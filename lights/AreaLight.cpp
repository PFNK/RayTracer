/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"
#include "math/geometry.h"
#include <vector>



namespace rt{

    AreaLight::AreaLight():LightSource(){}
    AreaLight::~AreaLight(){}

    /**
     * Prints light data
     * this function implements the abstract function of the base LightSource class
     */
    void AreaLight::printLightSource(){
        printf("I am a area light! \n");
        printf("v0 corner: %dpx, %dpx, %d \n", v0[0], v0[1], v0[2]);
    }
    
    Vec3f AreaLight::getPosition(){
        // Sample position using the points defining corners 
        float min_x = std::min(v0[0], std::min(v1[0], v2[0]));
        float max_x = std::max(v0[0], std::max(v1[0], v2[0]));
        float min_y = std::min(v0[1], std::min(v1[1], v2[1]));
        float max_y = std::max(v0[1], std::max(v1[1], v2[1]));
        float min_z = std::min(v0[2], std::min(v1[2], v2[2]));
        float max_z = std::max(v0[2], std::max(v1[2], v2[2]));
        // they must have 1 dimension the same:
        if(v0[0] == v1[0] && v0[0] == v2[0]){ // random from y and z
            float y = min_y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_y-min_y)));
            float z = min_z + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_z-min_z)));
            return Vec3f(v0[0], y, z);
        }
        if(v0[1] == v1[1] && v0[1] == v2[1]){ // random from x and z
            float x = min_x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_x-min_x)));
            float z = min_z + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_z-min_z)));
            return Vec3f(x, v0[1], z);
        }
        // random from y and x
        float y = min_y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_y-min_y)));
        float x = min_x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max_x-min_x)));
        return Vec3f(x, y, v0[2]);
        
	}

	Vec3f AreaLight::getId(){
		return id;
	}

	Vec3f AreaLight::getIs(){
		return is;
	}




} //namespace rt
