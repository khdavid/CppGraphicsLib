#pragma once

#include "material.h"

namespace MaterialsFactory
{
extern const Color Black;
extern const Color White;
extern const Color Red;
extern const Color Lime;
extern const Color Blue;
extern const Color Yellow;
extern const Color Aqua;
extern const Color Magenta;
extern const Color Silver;
extern const Color Gray;
extern const Color Maroon;
extern const Color Olive;
extern const Color Green;
extern const Color Purple;
extern const Color Teal;
extern const Color Navy;

Material Specular(const Color& color, float sharpness = 500);
Material Diffuse(const Color& color, float sharpness = 500);
};

