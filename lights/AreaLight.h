/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"
#include <time.h>

namespace rt{

class AreaLight:public LightSource{
public:

	//
	// Constructors
	//
	AreaLight();
	AreaLight(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f id, Vec3f is):v0(v0), v1(v1), v2(v2), id(id), is(is){
		srand(time(NULL)); //because getPosition uses rand()
	}

	//
	//Destructor
	//
	virtual ~AreaLight();

	void printLightSource();
	Vec3f getId();
	Vec3f getIs();
	Vec3f getPosition();


protected:
    Vec3f id;
    Vec3f is;
	Vec3f v0;
	Vec3f v1;
	Vec3f v2;
};



} //namespace rt




#endif /* AREALIGHT_H_ */
