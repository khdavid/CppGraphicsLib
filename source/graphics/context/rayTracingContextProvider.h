#pragma once
#include <memory>
#include "contextProvider.h"
//#include "commands/GLSLProgramsManager.h"

class GLSLProgramsManager;

class RayTracingContextProvider : public ContextProvider
{
public:
  RayTracingContextProvider();
private:
  std::unique_ptr<GLSLProgramsManager> spriteManager_;

};

