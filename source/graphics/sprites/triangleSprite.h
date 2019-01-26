#pragma once

#include <glew.h>
#include <geometryObjects/triangle.h>

class GLSLShaderToolBase;

class TriangleSprite
{
public:
  TriangleSprite();
  ~TriangleSprite();
  void render(int x, int y);

private:
  Triangle2D triangle_;
  GLuint vboPosition_ = 0;
  GLuint vboColor_ = 0;
  GLuint vboVertices_ = 0;

  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;
  GLint fadeUniform_ = 0;
  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
};

