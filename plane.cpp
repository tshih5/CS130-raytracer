#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray &ray, int part) const
{
    double dotp = dot(ray.direction, this->normal);
    if ((dotp <= -1.0 * small_t || dotp >= small_t) && dot((this->x1 - ray.endpoint), this->normal) / dot(ray.direction, this->normal) >= small_t)
    {
        double t = (dot(this->x1 - ray.endpoint, this->normal)) / dot(ray.direction, this->normal);
        return {this, t, part};
    }
    return {NULL, 0, -1};
}

vec3 Plane::Normal(const vec3 &point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo = -b.hi;
    return b;
}
