#include <vector>

#include "GLSL/GLObjects.h"
#include "utils/geometryUtils.h"
#include "GLSLProgramRayTracing.h"
#include "model/model.h"

namespace
{
// All the constants here have the counterparts on the GLSL side.
// So the changes should be done on both sides.
const char* cGlobalToCameraName = "globalToCamera";
const char* cSphereColorsName = "sphereColors";
const char* cSphereRadiusesName = "sphereRadiuses";
const char* cSphereCentersName = "sphereCenters";
const char* cSpheresCount = "spheresCount";
const size_t cMaxNumberOfSpheres = 100; 
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
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  glUniformMatrix4fv(globalToCameraUniform_, 1, false, glMatrix.data());

  initSpheresUniforms_();
}

void GLSLProgramRayTracing::initSpheresUniforms_()
{
  sphereColorsUniform_ = glGetUniformLocation(programId_, cSphereColorsName);
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
  std::vector<GLColor> colors;
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

    colors.push_back({
      material.diffuse.r,
      material.diffuse.g,
      material.diffuse.b });
  }
  glUniform1fv(sphereRadiusesUniform_, (GLsizei)spheresCount, (GLfloat*)radiuses.data());
  glUniform3iv(sphereColorsUniform_, (GLsizei)spheresCount, (GLint*)colors.data());
  glUniform3fv(sphereCentersUniform_, (GLsizei)spheresCount, (GLfloat*)centers.data());
}

void GLSLProgramRayTracing::render()
{
  auto glMatrix = GeometryUtils::convertToGL(globalToCamera_);
  glUniformMatrix4fv(globalToCameraUniform_, 1, true, glMatrix.data());
  renderSpheres_();

  GLSLProgramFragmentShader::render();
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

out vec4 outColor;
uniform mat4 globalToCamera;

const int cMaxNumberOfSpheres = 100; // has a copy counterpart on the C++ part
uniform int spheresCount = 0;

uniform ivec3 sphereColors[cMaxNumberOfSpheres];
uniform vec3 sphereCenters[cMaxNumberOfSpheres];
uniform float sphereRadiuses[cMaxNumberOfSpheres];

const float TOLERANCE = 1e-3;
const float TOLERANCE_SQR = 1e-6;

struct Ball
{
  vec3 center;
  float radius;
  vec3 color;
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


vec3 getPhongColor(vec3 color, vec3 normal, in Light light, in Ray reflectedRay)
{
  float diffuseFactor = max (0, dot(normal, -light.direction));
  float specularFactor = max(0, dot(reflectedRay.direction, -light.direction));
  specularFactor = pow(specularFactor, 200);
  return (0.6 + 0.4 * diffuseFactor) * color + 0.5 * specularFactor * light.color;
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

const vec3 blue = vec3(166, 202, 240) / 255;
const vec3 green = vec3(100, 240, 100) / 255;
const vec3 white = vec3(255, 255, 255) / 255;

void main()
{
  
  Ball balls[cMaxNumberOfSpheres];

  for (int i = 0; i < spheresCount; ++i)
  {
    balls[i].center = sphereCenters[i];
    balls[i].radius = sphereRadiuses[i];
    balls[i].color = sphereColors[i] / 255.0;
  }



  Ray ray;
  ray.point = gl_FragCoord.xyz;
  ray.direction = vec3(0, 0 , 1);
  ray.direction = ray.direction / sqrt(lenSqr(ray.direction));
  
  ray = transform(ray, globalToCamera);
  

  Light light;
  light.color = white;
  light.direction = normalized(vec3 (0, -2, -1));
  //light.direction = transformVector(light.direction, globalToCamera);
  
  float minDistanceSqr = 1e10;
  bool closestBallFound = false;
  vec3 closestIntersectionPoint;
  Ball closestBall;

  vec3 color = white;  

  for (int i = 0; i < spheresCount; ++i)
  {
    vec3 firstIntersectionPoint;  
    if (isRayHittingBall(ray, balls[i], firstIntersectionPoint))
    {
      float distanceSqr = lenSqr(firstIntersectionPoint - ray.point);
      if(distanceSqr < minDistanceSqr)
      {
        minDistanceSqr = distanceSqr;
        closestBall = balls[i];
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
    color = getPhongColor(closestBall.color, n, light, reflectedRay);
  }

  outColor = vec4(color, 1);
  //outColor = vec4(globalToCamera[0][0], globalToCamera[0][1], globalToCamera[0][2], 1);
}
  
)";
}
