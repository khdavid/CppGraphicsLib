#include <algorithm>

#include "sceneRotatingTool.h"
#include "geometryObjects/vector.h"
#include "utils/geometryUtils.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"

namespace
{
const float ROTATION_SPEED = 0.08f;
const Point3D CENTER_OF_ROTATION = Point3D(350, 200, 500);
const double SCROLLING_FACTOR = 50.0;
const double MIN_SCROLLING_FRACTION = 0.8;

}

SceneRotatingTool::SceneRotatingTool(GLSLProgramRayTracing & rayTracingProgram, InputEventObservable& inputEventObservable) :
  rayTracingProgram_(rayTracingProgram),
  inputEventObservable_(inputEventObservable)
{
  inputEventObservable_.addInputListener(this);
}

SceneRotatingTool::~SceneRotatingTool()
{
  inputEventObservable_.removeInputListener(this);
}

void SceneRotatingTool::onMouseClick(int x , int y)
{
  mousePoint_ = { x, y };
}

void SceneRotatingTool::onMouseMove(int x , int y)
{
  auto mousePointNew = Point2D(-x, y);
  auto motion = mousePointNew - mousePoint_;
  Vector3D motion3D = { motion[0], motion[1], 0 };
  auto rotationDirection = GeometryUtils::cross(motion3D, GeometryUtils::AXIS_Z);
  mousePoint_ = mousePointNew;
  auto rotation = GeometryUtils::createAffineRotation(rotationDirection, CENTER_OF_ROTATION, ROTATION_SPEED);
  auto globalToCamera = rayTracingProgram_.getGlobalToCamera();
  rayTracingProgram_.setGlobalToCamera(globalToCamera * rotation);
  rayTracingProgram_.render();
}

void SceneRotatingTool::onMouseScrolling(int velocity)
{
  auto fraction = 1 + velocity / SCROLLING_FACTOR;
  fraction = std::max(MIN_SCROLLING_FRACTION, fraction);
  
  auto globalToCamera = rayTracingProgram_.getGlobalToCamera();
  auto scalingMatrix = GeometryUtils::createAffineScaling(CENTER_OF_ROTATION, fraction);
  rayTracingProgram_.setGlobalToCamera(globalToCamera * scalingMatrix);
  rayTracingProgram_.render();
}
