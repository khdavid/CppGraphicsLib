#pragma once

struct Color
{
  int r;
  int g;
  int b;
};

Color operator*(const Color& color, double multiplier);
Color operator+(const Color& color1, const Color& color2);

struct Material
{
  Color ambient;
  Color diffuse;
  Color specular;
  float sharpness;
};

