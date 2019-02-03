#include <vector>

#include "nodes/graphicsNode.h"
#include "RayTracingSprite.h"




std::string RayTracingSprite::getFragmentShaderCode_() const
{
  return R"(
#version 130

out vec4 color;

struct Ball
{
  vec3 center;
  float radius;
};

struct Ray
{
  vec3 direction; 
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

bool isLineHittingBall(in Ray ray, in Ball ball)
{
  vec3 rVector = ball.center - ray.point;
  vec3 crossProduct = cross(rVector, ray.direction);
  float distanceSqr = dot(crossProduct, crossProduct) / dot(ray.direction, ray.direction);
  return distanceSqr <= sqr(ball.radius);
}

bool isRayHittingBall(in Ray ray, in Ball ball)
{
  return isInsideBall(ray.point, ball) ||
    (isLineHittingBall(ray, ball) && isRayStartsBeforeBall(ray, ball));
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
  
  if (isRayHittingBall(ray, ball))
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
