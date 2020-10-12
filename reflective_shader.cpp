#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
    Shade_Surface(const Ray &ray, const vec3 &intersection_point,
                  const vec3 &normal, int recursion_depth) const
{
    vec3 color;
    color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    Ray reflected_ray(intersection_point, -2.0 * dot(ray.direction, normal) * normal + ray.direction);
    color = color * (1 - reflectivity);
    if (recursion_depth != world.recursion_depth_limit)
    {
        return color + reflectivity * world.Cast_Ray(reflected_ray, recursion_depth + 1);
    }
    else
    {
        return color;
    }
}
