#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
	double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, (ray.endpoint - this->center));
	double c = dot(ray.endpoint - this->center, ray.endpoint - this->center) - (this->radius * this->radius);
	double discrim = (b * b) - (4 * a * c);
	if(discrim < 0){
			return {NULL, 0, 0};
	}
	
	double t1 = (-b + sqrt(discrim)) / (2 * a);
	double t2 = (-b - sqrt(discrim)) / (2 * a);
	if(t1 >= small_t || t2 >= small_t ){
		if(t2 < t1 && t2 >= small_t){
			return {this, t2, part};
		}else if(t1 < t2 && t2 >= small_t){
			return {this, t1, part};
		}

	}else{
			return {NULL, 0, 0};
	}
 
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
