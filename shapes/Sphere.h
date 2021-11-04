/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"

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

	// Vec3f getNormal(Vec3f point){
	// 	return (point - center).normalize();
	// }


private:

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
