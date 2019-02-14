#include <algorithm>
#include "material.h"


Color operator*(const Color& color, double multiplier)
{
  return {
    int(color.r * multiplier),
    int(color.g * multiplier),
    int(color.b * multiplier)
  };
}

Color operator*(double multiplier, const Color& color)
{
  return color * multiplier;
}

Color operator+(const Color& color1, const Color& color2)
{
  return {
    color1.r + color2.r,
    color1.g + color2.g,
    color1.b + color2.b
  };
}


