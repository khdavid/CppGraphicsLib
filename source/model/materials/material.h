#pragma once

struct Color
{
  int r = 0;
  int g = 0;
  int b = 0;
};

Color operator*(const Color& color, double multiplier);
Color operator*(double multiplier, const Color& color);
Color operator+(const Color& color1, const Color& color2);

struct Material
{
  Color ambient;
  Color diffuse;
  Color specular;
  float sharpness = 0;
  bool transparent = false;
};

