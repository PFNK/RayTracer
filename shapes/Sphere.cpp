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
		//-----------to be implemented -------------
		Vec3f centerToOrigin = ray->origin - center;
		// solve the quatratic equation at^2 + bt + x = 0
		// where a = ray_dir dot ray_dir
		// and b = 2 * spehre_center-to-origin dot ray_dir
		// and c = spehre_center-to-origin dot spehre_center-to-origin - radius^2
		float QE_a = ray->direction.dotProduct(ray->direction);
		float QE_b = 2.0 * centerToOrigin.dotProduct(ray->direction);
		float QE_c = centerToOrigin.dotProduct(centerToOrigin) - radius*radius;
		// calculate the discriminant b^2 - 4*a*c
		float QE_discr = (QE_b * QE_b) - (4 * QE_a * QE_c);
		// if negative disriminant - no real roots, ray misses sphere
		if(QE_discr < 0){
			h.point = Vec3f(-1,-1,-1);
			h.t = 0;
			h.normal = Vec3f(0,0,0);
		}	
		// else need to check the roots and choose closer one
		else{
			// find t = -b +- sqrt(discriminant) / 2*a
			float t_minus = (-QE_b - sqrt(QE_discr)) / (2.0 * QE_a);
			float t_plus = (-QE_b + sqrt(QE_discr)) / (2.0 * QE_a);
			h.t = std::min(t_minus, t_plus);
			if(h.t < 0) h.t = std::max(t_minus, t_plus);
			h.point = ray->origin + (h.t*ray->direction);
			h.normal = (h.point - center).normalize();
		}

		return h;

	}



} //namespace rt


