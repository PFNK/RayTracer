/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"
#include "Bounds.h"

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

	Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

	Bounds getBounds(){
		float max_x = std::max(v0[0], std::max(v1[0], std::max(v2[0], v3[0])));
		float max_y = std::max(v0[1], std::max(v1[1], std::max(v2[1], v3[1])));
		float max_z = std::max(v0[2], std::max(v1[2], std::max(v2[2], v3[2])));
		Vec3f max(max_x, max_y, max_z);

		float min_x = std::min(v0[0], std::min(v1[0], std::min(v2[0], v3[0])));
		float min_y = std::min(v0[1], std::min(v1[1], std::min(v2[1], v3[1])));
		float min_z = std::min(v0[2], std::min(v1[2], std::min(v2[2], v3[2])));
		Vec3f min(min_x, min_y, min_z);

		return Bounds(min, max);

	}


private:

    Vec3f v0;
	Vec3f v1;
	Vec3f v2;
	Vec3f v3;

};



} //namespace rt




#endif /* PLANE_H_ */
