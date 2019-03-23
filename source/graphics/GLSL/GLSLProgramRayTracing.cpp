#include <vector>

#include "GLSL/GLObjects.h"
#include "utils/geometryUtils.h"
#include "GLSLProgramRayTracing.h"
#include "model/model.h"
#include "utils/SDLUtils.h"

GLSLProgramRayTracing::GLSLProgramRayTracing(
  SDL_Window& window, const Model& model): GLSLProgramFragmentShader(window), model_(model)
{
  globalToCamera_ = GeometryUtils::createIdentityMatrix4D();
}

void GLSLProgramRayTracing::init()
{
  GLSLProgramFragmentShader::init();
  
  globalUniform_.globalToCamera = glGetUniformLocation(programId_, "globalToCamera");
  globalUniform_.screenSize = glGetUniformLocation(programId_, "screenSize");
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  auto screenSizes = SDLUtils::getScreenSizes();
  glUniform2i(globalUniform_.screenSize, screenSizes[0], screenSizes[1]);
  glUniformMatrix4fv(globalUniform_.globalToCamera, 1, false, glMatrix.data());

  initSpheresUniforms_();
}

void GLSLProgramRayTracing::initSpheresUniforms_()
{
  sphereMaterialUniform_.diffuse = glGetUniformLocation(programId_, "sphereDiffuseColors");
  sphereMaterialUniform_.specular = glGetUniformLocation(programId_, "sphereSpecularColors");
  sphereMaterialUniform_.ambient = glGetUniformLocation(programId_, "sphereAmbientColors");
  sphereMaterialUniform_.sharpness = glGetUniformLocation(programId_, "sphereSharpnessColors");
  sphereMaterialUniform_.transparent = glGetUniformLocation(programId_, "sphereTransparencies");

  spheresGeometryUniform_.radius = glGetUniformLocation(programId_, "sphereRadiuses");
  spheresGeometryUniform_.center = glGetUniformLocation(programId_, "sphereCenters");
  spheresGeometryUniform_.count = glGetUniformLocation(programId_, "spheresCount");
}

void GLSLProgramRayTracing::renderSpheres_()
{
  auto sphereObjects = model_.getSphereObjects();
  auto spheresCount = sphereObjects.size();

  std::vector<GLPosition> centers;
  std::vector<GLfloat> radiuses;
  std::vector<GLfloat> sharpnesses;
  std::vector<GLint> transparencies;
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

    sharpnesses.push_back(material.sharpness);

    transparencies.push_back(material.transparent);
  }
  glUniform3iv(sphereMaterialUniform_.diffuse, (GLsizei)spheresCount, (GLint*)diffuseColors.data());
  glUniform3iv(sphereMaterialUniform_.ambient, (GLsizei)spheresCount, (GLint*)ambientColors.data());
  glUniform3iv(sphereMaterialUniform_.specular, (GLsizei)spheresCount, (GLint*)specularColors.data());
  glUniform1fv(sphereMaterialUniform_.sharpness, (GLsizei)spheresCount, (GLfloat*)sharpnesses.data());
  glUniform1iv(sphereMaterialUniform_.transparent, (GLsizei)spheresCount, (GLint*)transparencies.data());

  glUniform3fv(spheresGeometryUniform_.center, (GLsizei)spheresCount, (GLfloat*)centers.data());
  glUniform1fv(spheresGeometryUniform_.radius, (GLsizei)spheresCount, (GLfloat*)radiuses.data());
  glUniform1i(spheresGeometryUniform_.count, (GLint)spheresCount);

}

void GLSLProgramRayTracing::render()
{
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  glUniformMatrix4fv(globalUniform_.globalToCamera, 1, true, glMatrix.data());
  renderSpheres_();

  GLSLProgramFragmentShader::render();
}

void GLSLProgramRayTracing::onWindowsResized(int x, int y)
{
  glUniform2i(globalUniform_.screenSize, x, y);
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
uniform float sphereSharpnessColors[cMaxNumberOfSpheres];
uniform int sphereTransparencies[cMaxNumberOfSpheres];

uniform vec3 sphereCenters[cMaxNumberOfSpheres];
uniform float sphereRadiuses[cMaxNumberOfSpheres];

const float TOLERANCE = 1e-3;
const float TOLERANCE_SQR = 1e-6;

struct Material
{
  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
  float sharpness;
  bool transparent;
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

vec3 getReflectedDirection(in Ray ray, in vec3 intersectionPoint, in Ball ball)
{
  vec3 n = normalized(intersectionPoint - ball.center);  
  vec3 direction = ray.direction - 2 * dot(ray.direction, n) * n;
  return direction;
}

//an infinite line is define by ray
bool getReflectedLine(in Ray ray, in Ball ball, out Ray reflected)
{
  vec3 secondIntersection;
  if (!isLineHittingBall(ray, ball, reflected.point, secondIntersection))
  {
    return false;
  }

  reflected.direction = getReflectedDirection(ray, reflected.point, ball);
  return true;
}

bool getReflectedRay(in Ray ray, in Ball ball, out Ray reflected)
{
  if (!isRayHittingBall(ray, ball, reflected.point))
  {
    return false;
  }

  reflected.direction = getReflectedDirection(ray, reflected.point, ball);
  return true;
}


vec3 getPhongColor(Material material, vec3 normal, in Light light, in Ray reflectedRay)
{
  float diffuseFactor = max (0, dot(normal, -light.direction));
  float specularFactor = max(0, dot(reflectedRay.direction, -light.direction));
  specularFactor = pow(specularFactor, material.sharpness);
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
  result.material.sharpness = sphereSharpnessColors[i];
  result.material.transparent = bool(sphereTransparencies[i]);

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

bool findClosestBallAlongLine(in Ray ray, out Ball ballFound, out vec3 closestIntersectionPoint)
{
  float minDistance = FLT_MAX;
  bool closestBallFound = false;

  for (int i = 0; i < spheresCount; ++i)
  {
    Ball ball = constructBall(i);
    vec3 firstIntersectionPoint, secondIntersection;  
    if (isLineHittingBall(ray, ball, firstIntersectionPoint, secondIntersection))
    {
      float distance = dot(firstIntersectionPoint - ray.point, ray.direction);
      if(distance < minDistance)
      {
        minDistance = distance;
        ballFound = ball;
        closestIntersectionPoint = firstIntersectionPoint;
        closestBallFound = true;
      }
    }
  }
  return closestBallFound;
}

Ray createRay()
{
  Ray ray;
  vec2 SDLCoordinates = getSDLCoordinates();
  ray.point = vec3(SDLCoordinates, 1000);
  ray.direction = vec3(0, 0 , 1);
  ray.direction = ray.direction / sqrt(lenSqr(ray.direction));
  ray = transform(ray, globalToCamera);
  return ray;
}
Light createLight()
{
  Light light;
  light.color = white;
  light.direction = normalized(vec3 (0, -2, -1));
  return light;
}


void main()
{
  Ray ray = createRay();
  Light light = createLight();
  
  vec3 color = white;  
  vec3 closestIntersectionPoint;
  Ball closestBall;
  if (findClosestBallAlongLine(ray, closestBall, closestIntersectionPoint))
  {
    Ray reflectedRay;
    getReflectedLine(ray, closestBall, reflectedRay);
    vec3 n = normalized(closestIntersectionPoint - closestBall.center);
    color = getPhongColor(closestBall.material, n, light, reflectedRay);
  }

  outColor = vec4(color, 1);
}
  
)";
}
