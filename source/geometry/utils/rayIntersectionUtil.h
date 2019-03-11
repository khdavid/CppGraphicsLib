#pragma once
#include <optional>

#include "geometryObjects/sphere.h"
#include "geometryObjects/ray.h"
namespace RayIntersectionUtil
{
std::optional<Point3D> isRayHittingSphere(const Ray& ray, const Sphere& sphere);
};

