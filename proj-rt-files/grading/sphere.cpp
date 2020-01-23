#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    //L is the vector from the center of the sphere to the endpoint of the ray
	vec3 L = this->center - ray.endpoint;
	double mag_L = L.magnitude();
	//tc is the magnitude of the projection of L onto the ray
	double tc = dot(L, ray.direction);
	if(tc < small_t){
		return {NULL, 0, 0};
	}
	//d is the distance between the center of the sphere and avector perpendicular 
	//to the ray that touches the center of the sphere
	
	double d = sqrt((tc * tc) - (mag_L * mag_L));
	if(d > this->radius){
		return {NULL, 0, 0};
	}	
	double t1c = sqrt((this->radius * this-> radius) - (d * d));
	double t1 = tc - t1c;
	
    return {this, t1, part};
 
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
