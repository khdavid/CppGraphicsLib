#include <vector>

#include "nodes/graphicsNode.h"
#include "RayTracingSprite.h"




std::string RayTracingSprite::getFragmentShaderCode_() const
{
  return R"(
#version 130

out vec4 color;

const float TOLERANCE = 1e-3;
const float TOLERANCE_SQR = 1e-6;

struct Ball
{
  vec3 center;
  float radius;
};

struct Ray
{
  vec3 direction; // normalized vector
  vec3 point;
};

float sqr(float value)
{
  return value * value;
}

float lenSqr(in vec3 value)
{
  return dot(value, value);
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
  // lenSqr(ray.direction) * t^2 - 2 * dot(ray.direction, centerVec) * t - sqr(ball.radius) = 0;

  float D = sqr(dot(ray.direction, centerVec)) + lenSqr(ray.direction) * sqr(ball.radius);
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

const vec4 blue = vec4(166, 202, 240, 255) / 255;
const vec4 white = vec4(255, 255, 255, 255) / 255;

void main()
{
  Ball ball;
  ball.center = vec3(200, 200, 200);
  ball.radius = 100;

  Ray ray;
  ray.point = gl_FragCoord.xyz;
  ray.direction = vec3(0, 0, 1);
  
  vec3 firstIntersectionPoint;  
  if (isRayHittingBall(ray, ball, firstIntersectionPoint))
  {
    color = blue;
  }
  else
  {
    color = white;
  }

}
  
)";
}
