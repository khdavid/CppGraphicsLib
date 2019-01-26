#pragma once

#include <glew.h>
#pragma  pack(push, 1)

struct Color
{
  GLubyte r;
  GLubyte g;
  GLubyte b;
  //GLubyte alpha;
};

struct Material
{
  Color color;
};

struct Position
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

struct Vertex
{
  Position position;
  Material material;
};

#pragma pack(pop)
