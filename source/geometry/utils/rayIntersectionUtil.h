#pragma once
#include <optional>

#include "geometryObjects/sphere.h"
#include "geometryObjects/ray.h"

struct Point2D;
struct Matrix4D;

namespace RayIntersectionUtil
{
std::optional<std::pair<Point3D, Point3D>> isLineHittingSphere(const Ray& ray, const Sphere& sphere);
std::optional<Point3D> isRayHittingSphere(const Ray& ray, const Sphere& sphere);
Ray getPickRay(const Point3D& coords, const Matrix4D& transform);
}

