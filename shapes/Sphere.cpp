/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

	Sphere::Sphere():Shape(){}
	Sphere::~Sphere(){}

	
	Vec3f Sphere::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
		Vec2f uv(-1,-1);
		Vec3f point = (hitPoint - center).normalize();
		if(material->hasTexture){
			float u = 0.5 + atan2(point[0], -point[1]) / (2 * M_PI);
			float v = 0.5 - asin(point[2]) / M_PI;
			uv = Vec2f(u,v);

		}
		return material->getColor(diffuse, specular, is, dist, uv);
	}


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
		h.dest = this;
		float t;
		//-----------to be implemented -------------
		Vec3f oc = ray->origin - center; //center - ray->origin;//
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
			if(h.t < 0) h.t = std::max(t_minus, t_plus);
			h.point = ray->origin + (h.t*ray->direction);
			h.normal = (h.point - center).normalize();
			// printf("sphere t_m t_p %f %f \n", t_minus, t_plus);
		}

		return h;

	}



} //namespace rt


