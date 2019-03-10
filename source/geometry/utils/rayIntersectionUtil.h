#pragma once
#include <optional>

#include "geometryObjects/sphere.h"
#include "geometryObjects/ray.h"
namespace RayIntersectionUtil
{

std::optional<Point3D> isIntersecting(const Sphere& sphere, const Ray& ray);
};

