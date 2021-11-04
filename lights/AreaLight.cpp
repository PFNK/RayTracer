/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"
#include "math/geometry.h"




namespace rt{

    AreaLight::AreaLight():LightSource(){}
    AreaLight::~AreaLight(){}

    /**
     * Prints light data
     * this function implements the abstract function of the base LightSource class
     */
    void AreaLight::printLightSource(){
        printf("I am a area light! \n");
        printf("position: %dpx, %dpx, %d \n", position[0], position[1], position[2]);
    }
    
    Vec3f AreaLight::getPosition(){
		return position;
	}

	Vec3f AreaLight::getId(){
		return id;
	}

	Vec3f AreaLight::getIs(){
		return is;
	}




} //namespace rt
