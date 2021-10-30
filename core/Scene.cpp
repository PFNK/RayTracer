/*
 * Scene.cpp
 *
 */
#include "Scene.h"




namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------
	Value& shapes = scenespecs["shapes"];
	Value& lights = scenespecs["lightsources"];

	//iterate through shapes
	std::cout<<"'shapes' contains "<<shapes.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < shapes.Size(); i++){ // Retrieve values through GetXXX() functions
	        printf("shapes[%d] = %s radius: %f \n", i,
	        		shapes[i].GetObject()["type"].GetString(),
					shapes[i].GetObject()["radius"].GetFloat());
	}

	//iterate through lightsources
	std::cout<<"'lightsources' contains "<<lights.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < lights.Size(); i++){ // Retrieve values through GetXXX() functions
	        printf("lightsources[%d] = %s \n", i, lights[i].GetObject()["type"].GetString());
	}
}



} //namespace rt
