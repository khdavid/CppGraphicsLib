#pragma once
#include "sphereObject.h"
struct Material;
struct Sphere;

namespace ObjectsFactory
{
std::unique_ptr<SphereObject> createSphereObject(Material material, Sphere sphere);
};

