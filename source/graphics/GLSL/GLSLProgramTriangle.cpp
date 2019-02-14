#include "GLSLProgramTriangle.h"

namespace
{
  const char* cVertexPositionName = "vertexPosition";
  const char* cVertexColorName = "vertexColor";
}
void GLSLProgramTriangle::init_(const std::vector<GLVertex>& vertices)
{
  GLSLProgramBase::init_();
  numOfVertices_ = vertices.size();

  glGenBuffers(1, &vboVertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLVertex) * numOfVertices_, vertices.data(), GL_STATIC_DRAW);

  vertexPositionAttr_ = glGetAttribLocation(programId_, cVertexPositionName);
  vertexColorAttr_ = glGetAttribLocation(programId_, cVertexColorName);

  glEnableVertexAttribArray(vertexPositionAttr_);
  glEnableVertexAttribArray(vertexColorAttr_);

  const int cVertexPositionDim = 3;
  glVertexAttribPointer(
    vertexPositionAttr_, // attribute
    cVertexPositionDim,              // number of elements per vertex, here (x, y, z)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    sizeof(GLVertex),                 // extra data between each position
    (const void *)offsetof(GLVertex, position));                // offset of first element


  const int cVertexColorDim = 3;
  glVertexAttribPointer(
    vertexColorAttr_, // attribute
    cVertexColorDim,              // number of elements per vertex, here (x,y)
    GL_UNSIGNED_BYTE,          // the type of each element
    GL_FALSE,          // take our values as-is
    sizeof(GLVertex),                 // no extra data between each position
    (const void *)offsetof(GLVertex, material));                // offset of first element
}

void GLSLProgramTriangle::render()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glDrawArrays(GL_TRIANGLES, 0, GLsizei(numOfVertices_));

  SDL_GL_SwapWindow(&window_);
}

GLSLProgramTriangle::GLSLProgramTriangle(SDL_Window & window):
  window_(window)
{}

GLSLProgramTriangle::~GLSLProgramTriangle()
{
  if (shaderProgram_)
  {
    glDeleteBuffers(1, &vboVertices_);
    glDisableVertexAttribArray(vertexColorAttr_);
    glDisableVertexAttribArray(vertexPositionAttr_);
  }
}

