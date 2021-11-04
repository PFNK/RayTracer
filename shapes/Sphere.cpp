/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

	Sphere::Sphere():Shape(){}
	Sphere::~Sphere(){}


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray* ray){
		Hit h;
		float t;
		//-----------to be implemented -------------
		Vec3f oc = center - ray->origin;//ray->origin - center;
		float a = ray->direction.dotProduct(ray->direction);
		float b = 2.0 * oc.dotProduct(ray->direction);
		float c = oc.dotProduct(oc) - radius*radius;
		float discriminant = b*b - 4*a*c;
		if(discriminant < 0){
			h.point = Vec3f(-1,-1,-1);
			h.t = 0;
			h.normal = Vec3f(0,0,0);
		}
		else{
			float t_minus = (-b - sqrt(discriminant)) / (2.0*a);
			float t_plus = (-b + sqrt(discriminant)) / (2.0*a);
			h.t = std::min(t_minus, t_plus);
			h.point = ray->origin - (h.t*ray->direction);
			h.normal = (h.point - center).normalize();
			// printf("sphere t_m t_p %f %f \n", t_minus, t_plus);
		}

		return h;

	}



} //namespace rt


