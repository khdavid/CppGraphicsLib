#pragma once

#include <glew.h>
#pragma  pack(push, 1)

struct GLColor
{
  GLint r;
  GLint g;
  GLint b;
  //GLubyte alpha;
};

struct GLMaterial
{
  GLColor color;
};

struct GLPosition
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

struct GLVertex
{
  GLPosition position;
  GLMaterial material;
};

struct GLTriangle
{
  GLVertex vertices[3];
};

#pragma pack(pop)
