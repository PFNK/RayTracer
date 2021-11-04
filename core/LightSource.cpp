/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "lights/AreaLight.h"
#include "lights/PointLight.h"

namespace rt{

	LightSource::~LightSource(){};


/**
 * Factory function that returns lightsource subclass based on lightsource specifications
 *
 * @param lightsourceSpecs light specifications json object
 *
 * @return lightsource subclass instance
 *
 */
LightSource* LightSource::createLightSource(Value& lightSpecs){

	//check if lightsourcetype is defined

	if (!lightSpecs.HasMember("type")){
		std::cerr<<"Lightsource type not specified"<<std::endl;
		exit(-1);
	}

	std::string lightType=lightSpecs["type"].GetString();

	// return lightsource object based on lightsource specs
	if (lightType.compare("pointlight")==0){
		return new PointLight( 
            Vec3f(lightSpecs["position"][0].GetFloat(), lightSpecs["position"][1].GetFloat(), lightSpecs["position"][2].GetFloat()),
			Vec3f(lightSpecs["id"][0].GetFloat(), lightSpecs["id"][1].GetFloat(), lightSpecs["id"][2].GetFloat()),
			Vec3f(lightSpecs["is"][0].GetFloat(), lightSpecs["is"][1].GetFloat(), lightSpecs["is"][2].GetFloat()));

	}
	else if (lightType.compare("arealight")==0){
		return new AreaLight(
            Vec3f(lightSpecs["position"][0].GetFloat(), lightSpecs["position"][1].GetFloat(), lightSpecs["position"][2].GetFloat()),
			Vec3f(lightSpecs["id"][0].GetFloat(), lightSpecs["id"][1].GetFloat(), lightSpecs["id"][2].GetFloat()),
			Vec3f(lightSpecs["is"][0].GetFloat(), lightSpecs["is"][1].GetFloat(), lightSpecs["is"][2].GetFloat()));
	}

	return 0;

}



} //namespace rt

