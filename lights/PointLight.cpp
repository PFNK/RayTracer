/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"



namespace rt{

    PointLight::PointLight():LightSource(){}
	PointLight::~PointLight(){}


    /**
     * Prints light data
     * this function implements the abstract function of the base LightSource class
     */
    void PointLight::printLightSource(){
        printf("I am a point light! \n");
        printf("position: %dpx, %dpx, %d \n", position[0], position[1], position[2]);
    }

    Vec3f PointLight::getPosition(){
		return position;
	}

	Vec3f PointLight::getId(){
		return id;
	}

	Vec3f PointLight::getIs() {
		return is;
	}


} //namespace rt
