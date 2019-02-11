#pragma once
#include <memory>

struct Material;
class SphereObject;
struct Sphere;

namespace ObjectsFactory
{
std::unique_ptr<SphereObject> createSphereObject(Material material, Sphere sphere);
};

