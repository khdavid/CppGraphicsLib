#include "materialsFactory.h"

namespace MaterialsFactory
{
const Color Black = { 0, 0, 0 };
const Color White = { 255, 255, 255 };
const Color Red = { 255, 0, 0 };
const Color Lime = { 0, 255, 0 };
const Color Blue = { 0, 0, 255 };
const Color Yellow = { 255, 255, 0 };
const Color Aqua = { 0, 255, 255 };
const Color Magenta = { 255, 0, 255 };
const Color Silver = { 192, 192, 192 };
const Color Gray = { 128, 128, 128 };
const Color Maroon = { 128, 0, 0 };
const Color Olive = { 128, 128, 0 };
const Color Green = { 0, 128, 0 };
const Color Purple = { 128, 0, 128 };
const Color Teal = { 0, 128, 128 };
const Color Navy = { 0, 0, 128 };


Color ambient;
Color diffuse;
Color specular;
float sharpness;

Material RedDiffuse()
{
  Material result;
  result.ambient = 0.2 * Red;
  result.diffuse = 0.8 * Red;
  result.sharpness = 30;
  return result;
}

}
