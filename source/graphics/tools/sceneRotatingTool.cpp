#include <algorithm>
#include <iostream>
#include "sceneRotatingTool.h"
#include "geometryObjects/vector.h"
#include "utils/geometryUtils.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"
#include "model/model.h"

namespace
{
const float ROTATION_SPEED = 0.08f;
const double MIN_SCROLLING_FRACTION = 0.8;
}//end of unnamed namespace

void SceneRotatingTool::onKeyPress(SDL_Keycode /*keyCode*/)
{
// to do rotation with ctrl here
}

void SceneRotatingTool::onMouseClickRight(int x , int y)
{
  mousePoint_ = { x, y };
  centerOfRotation_ = getCenterOfRotation_();
}

void SceneRotatingTool::onMouseMoveRight(int x , int y)
{
  auto mousePointNew = Point2D(x, y);
  auto motion = mousePointNew - mousePoint_;
  auto motion3D = Vector3D{ motion[0], motion[1], 0 };
  auto rotationDirection = GeometryUtils::cross(GeometryUtils::AXIS_Z, motion3D);
  mousePoint_ = mousePointNew;
  std::cout << "centerOfRotation: " << centerOfRotation_[0] << " " <<
    centerOfRotation_[1] << " " << centerOfRotation_[2] << std::endl;
  auto rotation = GeometryUtils::createAffineRotation(rotationDirection, centerOfRotation_, ROTATION_SPEED);
  auto globalToCamera = rayTracingProgram_.getGlobalToCamera();
  rayTracingProgram_.setGlobalToCamera(globalToCamera * rotation);
  rayTracingProgram_.render();
}

void SceneRotatingTool::onMouseScrolling(double velocity)
{
  auto fraction = 1 + velocity;
  fraction = std::max(MIN_SCROLLING_FRACTION, fraction);
  
  auto globalToCamera = rayTracingProgram_.getGlobalToCamera();
  centerOfRotation_ = getCenterOfRotation_();
  auto scalingMatrix = GeometryUtils::createAffineScaling(centerOfRotation_, fraction);
  rayTracingProgram_.setGlobalToCamera(globalToCamera * scalingMatrix);
  rayTracingProgram_.render();
}

Point3D SceneRotatingTool::getCenterOfRotation_() const
{
  auto centerOfRotation = GeometryUtils::ZERO_POINT;
  const auto& sphereObjects = model_.getSphereObjects();
  const auto numSphereObjects = sphereObjects.size();

  for (const auto& sphereObject : sphereObjects)
  {
    auto centerRadVector = (sphereObject->getSphere().center - GeometryUtils::ZERO_POINT) / double(numSphereObjects);
    centerOfRotation += centerRadVector;
  }

  return centerOfRotation;
}
