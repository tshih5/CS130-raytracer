#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray &ray, int part) const
{
    //calculate intersection
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, (ray.endpoint - this->center));
    double c = dot(ray.endpoint - this->center, ray.endpoint - this->center) - (this->radius * this->radius);
    double discrim = (b * b) - (4 * a * c);
    if (discrim < 0)
    {
        return {NULL, 0, 0};
    }

    double t = (-b - sqrt(discrim)) / (2 * a);
    if (t >= small_t)
    {
        return {this, t, part};
    }
    else
    {
        return {NULL, 0, -1};
    }
}

vec3 Sphere::Normal(const vec3 &point, int part) const
{
    vec3 normal;
    // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
