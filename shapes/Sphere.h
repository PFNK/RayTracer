/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"
#include "shapes/Bounds.h"

namespace rt{

class Sphere:public Shape{

public:

	//
	// Constructors
	//
	Sphere();
	Sphere(Vec3f center, float radius):center(center), radius(radius){};

	// virtual ~Sphere();

	//
	//Destructor
	//
	// ~Sphere(){};
	virtual ~Sphere();


	//
	// Functions that need to be implemented, since Sphere is a subclass of Shape
	//
	
	Hit intersect(Ray* ray);

	Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

	Bounds getBounds(){
		// printf("center %f %f %f \n", center[0], center[1], center[2]);
		Vec3f max = Vec3f(center[0]+radius, center[1]+radius, center[2]+radius);
		Vec3f min = Vec3f(center[0]-radius, center[1]-radius, center[2]-radius);
		// printf("max %f %f %f \n", max[0], max[1], max[2]);
		// printf("min %f %f %f \n", min[0], min[1], min[2]);


		return Bounds(min, max);
	}




private:

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
