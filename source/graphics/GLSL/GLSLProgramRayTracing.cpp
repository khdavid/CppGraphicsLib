#include <vector>

#include "GLSL/GLObjects.h"
#include "utils/geometryUtils.h"
#include "GLSLProgramRayTracing.h"
#include "model/model.h"
#include "utils/SDLUtils.h"

namespace
{
// All the constants here have the counterparts on the GLSL side.
// So the changes should be done on both sides.
const char* cGlobalToCameraName = "globalToCamera";
const char* cScreenSize = "screenSize";
const char* cSphereDiffuseColorsName = "sphereDiffuseColors";
const char* cSphereSpecularColorsName = "sphereSpecularColors";
const char* cSphereAmbientColorsName = "sphereAmbientColors";
const char* cSphereRadiusesName = "sphereRadiuses";
const char* cSphereCentersName = "sphereCenters";
const char* cSpheresCount = "spheresCount";
const size_t cMaxNumberOfSpheres = 3; 
}


GLSLProgramRayTracing::GLSLProgramRayTracing(
  SDL_Window& window, const Model& model): GLSLProgramFragmentShader(window), model_(model)
{
  globalToCamera_ = GeometryUtils::createIdentityMatrix4D();
}

void GLSLProgramRayTracing::init()
{
  GLSLProgramFragmentShader::init();
  
  globalToCameraUniform_ = glGetUniformLocation(programId_, cGlobalToCameraName);
  screenSizeUniform_ = glGetUniformLocation(programId_, cScreenSize);
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  glUniformMatrix4fv(globalToCameraUniform_, 1, false, glMatrix.data());
  auto screenSizes = SDLUtils::getScreenSizes();
  glUniform2i(screenSizeUniform_, screenSizes[0], screenSizes[1]);

  initSpheresUniforms_();
}

void GLSLProgramRayTracing::initSpheresUniforms_()
{
  sphereDiffuseColorsUniform_ = glGetUniformLocation(programId_, cSphereDiffuseColorsName);
  sphereSpecularColorsUniform_ = glGetUniformLocation(programId_, cSphereSpecularColorsName);
  sphereAmbientColorsUniform_ = glGetUniformLocation(programId_, cSphereAmbientColorsName);
  sphereRadiusesUniform_ = glGetUniformLocation(programId_, cSphereRadiusesName);
  sphereCentersUniform_ = glGetUniformLocation(programId_, cSphereCentersName);
  spheresCountUniform_ = glGetUniformLocation(programId_, cSpheresCount);
}

void GLSLProgramRayTracing::renderSpheres_()
{
  auto sphereObjects = model_.getSphereObjects();
  auto spheresCount = sphereObjects.size();
  
  glUniform1i(spheresCountUniform_, (GLint)spheresCount);

  std::vector<GLPosition> centers;
  std::vector<GLfloat> radiuses;
  std::vector<GLColor> diffuseColors;
  std::vector<GLColor> specularColors;
  std::vector<GLColor> ambientColors;
  for (const auto& sphereObject : sphereObjects)
  {
    const auto& sphere = sphereObject->getSphere();
    const auto& center = sphere.center;
    const auto& material = sphereObject->getMaterial();

    centers.push_back({
      GLfloat(center[0]),
      GLfloat(center[1]),
      GLfloat(center[2]) });

    radiuses.push_back(GLfloat(sphere.radius));

    diffuseColors.push_back({
      material.diffuse.r,
      material.diffuse.g,
      material.diffuse.b });

    specularColors.push_back({
      material.specular.r,
      material.specular.g,
      material.specular.b });

    ambientColors.push_back({
      material.ambient.r,
      material.ambient.g,
      material.ambient.b });
  }
  glUniform1fv(sphereRadiusesUniform_, (GLsizei)spheresCount, (GLfloat*)radiuses.data());
  glUniform3iv(sphereDiffuseColorsUniform_, (GLsizei)spheresCount, (GLint*)diffuseColors.data());
  glUniform3iv(sphereAmbientColorsUniform_, (GLsizei)spheresCount, (GLint*)ambientColors.data());
  glUniform3iv(sphereSpecularColorsUniform_, (GLsizei)spheresCount, (GLint*)specularColors.data());
  glUniform3fv(sphereCentersUniform_, (GLsizei)spheresCount, (GLfloat*)centers.data());
}

void GLSLProgramRayTracing::render()
{
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  glUniformMatrix4fv(globalToCameraUniform_, 1, true, glMatrix.data());
  renderSpheres_();

  GLSLProgramFragmentShader::render();
}

void GLSLProgramRayTracing::onWindowsResized(int x, int y)
{
  glUniform2i(screenSizeUniform_, x, y);
  GLSLProgramBase::onWindowsResized(x, y);
}

Matrix4D GLSLProgramRayTracing::getGlobalToCamera() const
{
  return globalToCamera_;
}

void GLSLProgramRayTracing::setGlobalToCamera(Matrix4D matrix)
{
  globalToCamera_ = std::move(matrix);
}

std::string GLSLProgramRayTracing::getFragmentShaderCode_() const
{
  return R"(
#version 130

#define FLT_MAX 3.402823466e+38;
out vec4 outColor;
uniform mat4 globalToCamera;
uniform ivec2 screenSize;

const int cMaxNumberOfSpheres = 100; // has a copy counterpart on the C++ part
uniform int spheresCount = 0;

uniform ivec3 sphereDiffuseColors[cMaxNumberOfSpheres];
uniform ivec3 sphereSpecularColors[cMaxNumberOfSpheres];
uniform ivec3 sphereAmbientColors[cMaxNumberOfSpheres];

uniform vec3 sphereCenters[cMaxNumberOfSpheres];
uniform float sphereRadiuses[cMaxNumberOfSpheres];

const float TOLERANCE = 1e-3;
const float TOLERANCE_SQR = 1e-6;

struct Material
{
  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
};

struct Ball
{
  vec3 center;
  float radius;
  Material material;
};

struct Ray
{
  vec3 direction; // normalized vector
  vec3 point;
};

struct Light
{
  vec3 direction;
  vec3 color;
};

float sqr(float value)
{
  return value * value;
}

float lenSqr(in vec3 vec)
{
  return dot(vec, vec);
}

vec3 normalized(in vec3 vec)
{
  return vec / sqrt(lenSqr(vec));
}

bool isInsideBall(in vec3 point, in Ball ball)
{
  vec3 rVector = point - ball.center;
  return dot(rVector, rVector) <= sqr(ball.radius);
}

bool isRayStartsBeforeBallCenter(in Ray ray, in Ball ball)
{
  vec3 rVector = ball.center - ray.point;
  return dot(rVector, ray.direction) >= 0;  
}

bool isRayStartsBeforeBall(in Ray ray, in Ball ball)
{
  return isRayStartsBeforeBallCenter(ray, ball) &&
    !isInsideBall(ray.point, ball);
}

bool isRayStartsAfterBall(in Ray ray, in Ball ball)
{
  return !isRayStartsBeforeBallCenter(ray, ball) &&
    !isInsideBall(ray.point, ball);
}

bool isLineHittingBall(in Ray ray, in Ball ball, out vec3 firstIntersection, out vec3 secondIntersection)
{
  vec3 centerVec = ball.center - ray.point;

  // we should solve the quadratic equation:
  // lenSqr(t * ray.direction - centerVec) = sqr(ball.radius);
  // lenSqr(ray.direction) * t^2 - 2 * dot(ray.direction, centerVec) * t + lenSqr(centerVec) - sqr(ball.radius) = 0;

  float D = sqr(dot(ray.direction, centerVec)) - lenSqr(ray.direction) * (lenSqr(centerVec) - sqr(ball.radius));
  if (D < 0)
  {
    return false;
  }
  float t1 = (dot(ray.direction, centerVec) - sqrt(D)) / lenSqr(ray.direction);
  float t2 = (dot(ray.direction, centerVec) + sqrt(D)) / lenSqr(ray.direction);
  
  firstIntersection = ray.point + t1 * ray.direction;  
  secondIntersection = ray.point + t2 * ray.direction;  
  return true;
}

bool isRayHittingBall(in Ray ray, in Ball ball, out vec3 firstIntersection)
{
  if (isRayStartsAfterBall(ray, ball))
  {
    return false;
  }

  vec3 secondIntersection;
  if (isLineHittingBall(ray, ball, firstIntersection, secondIntersection))
  {
    if (isInsideBall(ray.point, ball))
    {
      firstIntersection = secondIntersection;
    } 
    
    return true;
  }

  return false;
}

bool getReflectedRay(in Ray ray, in Ball ball, out Ray reflected)
{
  if (!isRayHittingBall(ray, ball, reflected.point))
  {
    return false;
  }

  vec3 n = normalized(reflected.point - ball.center);  
  reflected.direction = ray.direction - 2 * dot(ray.direction, n) * n;
  return true;
}


vec3 getPhongColor(Material material, vec3 normal, in Light light, in Ray reflectedRay)
{
  float diffuseFactor = max (0, dot(normal, -light.direction));
  float specularFactor = max(0, dot(reflectedRay.direction, -light.direction));
  specularFactor = pow(specularFactor, 200);
  return 
    material.ambient + 
    material.diffuse * diffuseFactor + 
    material.specular * specularFactor;
}

vec3 transformVector(in vec3 vector, in mat4 transform)
{
  vec3 result;
  result = (transform * vec4(vector, 0)).xyz;
  result = normalized(result);
  return result;
}

vec3 transformPoint(in vec3 point, in mat4 transform)
{
  vec3 result;
  result = (transform * vec4(point, 1)).xyz;
  return result;
}

Ray transform(in Ray ray, in mat4 transform)
{
  Ray result;
  result.point = transformPoint(ray.point, transform);
  result.direction = transformVector(ray.direction, transform);
  return result;
}

Ball constructBall(int i)
{
  Ball result;
  result.center = sphereCenters[i];
  result.radius = sphereRadiuses[i];
  result.material.diffuse = sphereDiffuseColors[i] / 255.0;
  result.material.ambient = sphereAmbientColors[i] / 255.0;
  result.material.specular = sphereSpecularColors[i] / 255.0;
  return result;
}

const vec3 blue = vec3(166, 202, 240) / 255;
const vec3 green = vec3(100, 240, 100) / 255;
const vec3 white = vec3(255, 255, 255) / 255;

vec2 getSDLCoordinates()
{
  vec2 result = gl_FragCoord.xy;
  result.y = screenSize.y - result.y;
  return result;
}

void main()
{
  Ray ray;
  vec2 SDLCoordinates = getSDLCoordinates();
  ray.point = vec3(SDLCoordinates, -1e4);

  ray.direction = vec3(0, 0 , 1);
  ray.direction = ray.direction / sqrt(lenSqr(ray.direction));
  
  ray = transform(ray, globalToCamera);
  

  Light light;
  light.color = white;
  light.direction = normalized(vec3 (0, -2, -1));
  //light.direction = transformVector(light.direction, globalToCamera);
  
  float minDistanceSqr = FLT_MAX;
  bool closestBallFound = false;
  vec3 closestIntersectionPoint;
  Ball closestBall;

  vec3 color = white;  

  for (int i = 0; i < spheresCount; ++i)
  {
    Ball ball = constructBall(i);
    vec3 firstIntersectionPoint;  
    if (isRayHittingBall(ray, ball, firstIntersectionPoint))
    {
      float distanceSqr = lenSqr(firstIntersectionPoint - ray.point);
      if(distanceSqr < minDistanceSqr)
      {
        minDistanceSqr = distanceSqr;
        closestBall = ball;
        closestIntersectionPoint = firstIntersectionPoint;
        closestBallFound = true;
      }
    }
  }

  if (closestBallFound)
  {
    Ray reflectedRay;
    getReflectedRay(ray, closestBall, reflectedRay);
    vec3 n = normalized(closestIntersectionPoint - closestBall.center);
    color = getPhongColor(closestBall.material, n, light, reflectedRay);
  }

  outColor = vec4(color, 1);
  //outColor = vec4(globalToCamera[0][0], globalToCamera[0][1], globalToCamera[0][2], 1);
}
  
)";
}
