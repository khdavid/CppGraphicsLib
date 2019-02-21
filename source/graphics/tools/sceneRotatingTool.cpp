#include "sceneRotatingTool.h"
#include "geometryObjects/vector.h"
#include "utils/geometryUtils.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"

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
  auto rotation = GeometryUtils::createAffineRotation(rotationDirection, Point3D(350, 200, 500), 0.04f);
  auto globalToCamera = rayTracingProgram_.getGlobalToCamera();
  rayTracingProgram_.setGlobalToCamera(globalToCamera * rotation);
  rayTracingProgram_.render();
}
