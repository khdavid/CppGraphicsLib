#pragma once
#include <sdl.h>
#include "contextProvider.h"

class InputEventObservable;
class Model;
class SceneRotatingTool;
class ObjectsMovingTool;

class RayTracingContextProvider : public ContextProvider
{
public:
  RayTracingContextProvider(SDL_Window& window, InputEventObservable& inputEventObservable);
  ~RayTracingContextProvider();
private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<SceneRotatingTool> sceneRotatingTool_;
  std::unique_ptr<ObjectsMovingTool> objectsMovingTool_;
};

