/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{
	RayType raytype;
	Vec3f origin;
	Vec3f direction;
};

class Shape; // so that Hit can contain Shape
struct Hit{
	Vec3f point; //point where ray hits a shape
	float t;
	Vec3f normal;
	int bounces;
	Shape* dest;

};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
