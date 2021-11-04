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

	//
	// print function (implementing abstract function of base class)
	//
	void printLightSource();
	Vec3f getId();
	Vec3f getIs();
	Vec3f getPosition();
	// Getters and Setters
	// //
	// Vec3f getPosition() const {
	// 	return position;
	// }

	// Vec3f getId() const {
	// 	return id;
	// }

	// Vec3f getIs() const {
	// 	return is;
	// }

	void setPosition(Vec3f pos) {
		this->position = pos;
	}

private:
	Vec3f position;
    Vec3f id;
    Vec3f is;
};



} //namespace rt




#endif /* POINTLIGHT_H_ */
