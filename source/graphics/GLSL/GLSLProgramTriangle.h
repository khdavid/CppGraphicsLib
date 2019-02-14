#pragma once
#include <glew.h>
#include <vector>

#include "nodes/graphicsNode.h"
#include "GLSLProgramBase.h"

class GLSLProgramTriangle : public GLSLProgramBase
{
public:
  GLSLProgramTriangle(SDL_Window& window);
  ~GLSLProgramTriangle();
  virtual void render() override;
protected:
    void init_(const std::vector<GLVertex>& vertices);

private:
  size_t numOfVertices_ = 0;
  GLuint vboVertices_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;
  SDL_Window& window_;

};

