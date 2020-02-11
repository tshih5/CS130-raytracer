#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{

	double dist = 0;
    if(part >= 0){														//check specified part
		if(debug_pixel){
			std::cout << "entered mesh intersection" << std::endl;
		}
		if(Intersect_Triangle(ray, part, dist)){
			return {this, dist, part};
		}
	}else{																//check against all parts and return intersected hit	
		for(unsigned i = 0; i < triangles.size(); ++i){
			if(Intersect_Triangle(ray, i, dist)){
				return {this, dist, (int)i};
			}
		}
		return {NULL, 0, 0};
	}
	return {NULL, 0 , 0};
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    vec3 a = vertices[triangles[part][0]];
    vec3 b = vertices[triangles[part][1]];
    vec3 c = vertices[triangles[part][2]];
    vec3 ab = b - a;													//get two edge vectors and calculate cross product for the normal
    vec3 ac = c - a;
    if(false){
		std::cout << "a: " << a << " b: " << b << " c: " << c <<std::endl;
		std::cout << "ab: " << ab << " ac: " << ac << std::endl;
		std::cout << "normal: " << cross(ab, ac).normalized() << std::endl;
	}
    return cross(ab, ac).normalized();
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    TODO;
    vec3 x(0, 0, 0);
    ivec3 triangle = triangles[tri];
    vec3 normal = Normal(x, tri);
    vec3 a, b, c, ab, ac;
    a = vertices[triangle[0]];
    b = vertices[triangle[1]];
    c = vertices[triangle[2]];
    ab = b - a;													//get two edge vectors
    ac = c - a;
	//calculate if ray intersects triangle.
	double dotp = dot(ray.direction, normal);
    if((dotp <= -1.0 * small_t || dotp >= small_t) && dot((a - ray.endpoint), normal) / dot(ray.direction, normal) >= small_t){ //ray intersects plane created by the triangle.
		double t = (dot(a - ray.endpoint, normal)) / dot(ray.direction, normal);
		vec3 intersection_point = ray.endpoint + t * ray.direction;																// this is point p for barycentric coordinates
		vec3 w = intersection_point - a;
		double bet, gam;
		bet = dot(w, cross(normal, ac)) / dot(ab, cross(normal, ac));
		gam = dot(w, cross(normal, ab)) / dot(ac, cross(normal, ab));
		if(bet > -weight_tolerance && gam > -weight_tolerance && (1 - bet - gam) > -weight_tolerance){
			dist = t;
			return true;
		}
	}else{
		return false;
	}
	return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
