#pragma once
#include <optional>

#include "geometryObjects/sphere.h"
#include "geometryObjects/ray.h"

struct Point2D;
struct Matrix4D;

namespace RayIntersectionUtil
{
std::optional<Point3D> isRayHittingSphere(const Ray& ray, const Sphere& sphere);
Ray getPickRay(const Point3D& coords, const Matrix4D& transform);
}

