#pragma once

#include <glew.h>
#include <geometryObjects/triangle.h>

class GLSLShaderToolBase;

class TriangleSprite
{
public:
  TriangleSprite();
  ~TriangleSprite();
  void init();
  void render(int x, int y);

private:
  std::string getVertexShaderCode_() const;
  std::string getFragmentShaderCode_() const;
  GLuint vboVertices_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;
  GLint fadeUniform_ = 0;
  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
};

