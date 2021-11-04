/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"

namespace rt{

class Plane:public Shape{

public:

	//
	// Constructors
	//
	Plane();
	Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3):v0(v0), v1(v1), v2(v2), v3(v3){};

	// virtual ~Plane();

	//
	//Destructor
	//
	virtual ~Plane();


	//
	// Functions that need to be implemented, since Plane is a subclass of Shape
	//
	Hit intersect(Ray* ray);
	Vec3f getNormal(Vec3f point){
		return ((v1-v0).crossProduct(v3-v0)).normalize();
	};

	Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

private:

    Vec3f v0;
	Vec3f v1;
	Vec3f v2;
	Vec3f v3;

};



} //namespace rt




#endif /* PLANE_H_ */
