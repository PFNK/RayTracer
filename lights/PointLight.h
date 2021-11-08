/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"


namespace rt{

class PointLight: public LightSource{

public:

	//
	// Constructors
	//
	PointLight();
	PointLight(Vec3f position, Vec3f id, Vec3f is):position(position), id(id), is(is){};

	//
	//Destructor
	//
	virtual ~PointLight();


	void printLightSource();
	Vec3f getId();
	Vec3f getIs();
	Vec3f getPosition();

private:
	Vec3f position;
    Vec3f id;
    Vec3f is;
};



} //namespace rt




#endif /* POINTLIGHT_H_ */
