#pragma once

struct Color
{
  wchar_t r;
  wchar_t g;
  wchar_t b;
};

struct Material
{
  Color ambient;
  Color diffuse;
  Color specular;
  float sharpness;
};

