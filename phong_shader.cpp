#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
    Shade_Surface(const Ray &ray, const vec3 &intersection_point,
                  const vec3 &normal, int recursion_depth) const
{
    vec3 color;
    //determine the color
    color = color_ambient * world.ambient_color * world.ambient_intensity;
    Hit hit;
    for (unsigned i = 0; i < world.lights.size(); ++i)
    {
        vec3 l = world.lights.at(i)->position - intersection_point; //light vector (surface to light)
        if (world.enable_shadows)
        {
            Ray temp;
            temp.endpoint = intersection_point; //temp ray from surface to light
            temp.direction = l.normalized();
            hit = world.Closest_Intersection(temp); //find the closest intersection with temp
            if (hit.object && hit.dist < l.magnitude())
            {                 //if an object is found to be between the light source and surface,
                return color; //skip adding diffuse and specular reflection
            }
        }

        vec3 light_color = world.lights.at(i)->Emitted_Light(ray.direction) / l.magnitude_squared(); //determine color of world light

        double diffuse_intensity = std::max(dot(l.normalized(), normal), 0.0); //get I_d
        color += diffuse_intensity * light_color * color_diffuse;              //R_d * L_d * diffuse_intensity

        vec3 ref_dir = ((2 * dot(l, normal) * normal) - l).normalized();                                    //ref_dir = reflection direction
        double specular_intensity = pow(std::max(dot(ref_dir, (ray.direction * -1)), 0.0), specular_power); //ray.direciton = view direction, get I_s
        color += specular_intensity * light_color * color_specular;                                         //R_s * L_s * specular_intensity
        if (debug_pixel)
            std::cout << "diffuse color" << diffuse_intensity * light_color * color_diffuse << std::endl;
    }

    return color;
}
