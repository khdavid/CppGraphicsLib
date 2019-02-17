#pragma once
#include <memory>
#include "contextProvider.h"

class GLSLProgramsManager;

class RayTracingContextProvider : public ContextProvider
{
public:
  RayTracingContextProvider();
  ~RayTracingContextProvider();
private:
  std::unique_ptr<GLSLProgramsManager> spriteManager_;

};

