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
bool isInsideBall (in vec3 point, in Ball ball)
{
  vec3 rVector = point - ball.center;
  return dot(rVector, rVector) <= sqr(ball.radius);
}

bool isRayStartsBeforeBall(in Ray ray, in Ball ball)
{
  vec3 rVector = ball.center - ray.point;
  return dot(rVector, ray.direction) >= 0;  
}

vec3 getNormalToCrossSection(in Ray ray, in Ball ball)
{
  vec3 rVector = ball.center - ray.point;
  vec3 crossProduct = cross(rVector, ray.direction);
  float crossProductLenSqr = dot(crossProduct, crossProduct);
  if (crossProductLenSqr < TOLERANCE_SQR)
  {
    return vec3(-ray.direction.y, ray.direction.x, ray.direction.z);
  }  

  return crossProduct / sqrt(crossProductLenSqr);
}

bool isLineHittingBall(in Ray ray, in Ball ball, out vec3 firstIntersection, out vec3 secondIntersection)
{
  vec3 rVector = ball.center - ray.point;
  vec3 crossProduct = cross(rVector, ray.direction);
  float distanceSqr = dot(crossProduct, crossProduct);
  if (distanceSqr <= sqr(ball.radius))
  {
    float sinAlpha = sqrt(distanceSqr) / ball.radius;
    float alpha = asin(sinAlpha);
    vec3 centerProjOnBallAlongDir = ball.center - ball.radius * ray.direction;
    vec3 normalToCrossSection = getNormalToCrossSection(ray, ball);
    
    return true;
  }
  
  return false;
}

bool isRayHittingBall(in Ray ray, in Ball ball, out vec3 firstIntersection)
{
  vec3 secondIntersection;
  isLineHittingBall(ray, ball, firstIntersection, secondIntersection);
  //return isInsideBall(ray.point, ball) ||
  //    (isLineHittingBall(ray, ball, firstIntersection, secondIntersection) && isRayStartsBeforeBall(ray, ball));
  return true;
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
