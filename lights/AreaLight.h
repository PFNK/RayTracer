/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"

namespace rt{

class AreaLight:public LightSource{
public:

	//
	// Constructors
	//
	AreaLight();
	AreaLight(Vec3f position, Vec3f id, Vec3f is):position(position), id(id), is(is){}

	//
	//Destructor
	//
	virtual ~AreaLight();
	//
	// print function (implementing abstract function of base class)
	//
	void printLightSource();
	Vec3f getId();
	Vec3f getIs();
	Vec3f getPosition();


	// Vec3f AreaLight::getPosition() const {
	// 	return position;
	// }

	// Vec3f getId() const {
	// 	return id;
	// }

	// Vec3f getIs() const {
	// 	return is;
	// }

	// void setPosition(Vec3f pos) {
	// 	this->position = pos;
	// }

protected:
	Vec3f position;
    Vec3f id;
    Vec3f is;

};



} //namespace rt




#endif /* AREALIGHT_H_ */
