/*
 * Scene.cpp
 *
 */
// #define _USE_MATH_DEFINES

#include "Scene.h"
#include "shapes/Sphere.h"
#include <cmath>
#include "shapes/BVH.h"

namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------
	Value& jsonShapes = scenespecs["shapes"];
	Value& jsonLights = scenespecs["lightsources"];
	backgroundColor = Vec3f(scenespecs["backgroundcolor"][0].GetFloat(), scenespecs["backgroundcolor"][1].GetFloat(), scenespecs["backgroundcolor"][2].GetFloat());
	std::vector<Shape*> shapesForBVH;

	//iterate through shapes
	std::cout<<"Number of shapes in scene: "<<jsonShapes.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < jsonShapes.Size(); i++){ // Retrieve values through GetXXX() functions
		printf("shapes[%d] = %s \n", i, jsonShapes[i].GetObject()["type"].GetString());
		Shape* p = Shape::createShape(jsonShapes[i]);
		shapesForBVH.push_back(p);
	}

	Shape* bvh = Shape::createBVH(shapesForBVH);
	sceneShapes.push_back(bvh);
	
	// uncomment below to not use BVH
	// sceneShapes=shapesForBVH;

	//iterate through lightsources
	std::cout<<"Number of lightsources in scene: "<<jsonLights.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < jsonLights.Size(); i++){ // Retrieve values through GetXXX() functions
		printf("lightsources[%d] = %s \n", i, jsonLights[i].GetObject()["type"].GetString());
		lightSources.push_back(LightSource::createLightSource(jsonLights[i]));
	}
}

Vec3f Scene::castRay(Ray* ray){
	float t = INFINITY;
	Vec3f colorOfHit = backgroundColor;
	
	for (int i=0; i < sceneShapes.size(); i++){
		Hit hit = sceneShapes[i]->intersect(ray);
		Vec3f intensity(0,0,0);
		Vec3f L_m, N, V, R, H, diffuse;
		float dist, specular;

		if (hit.t > 0){
			// if it hits the object and if it is closer hit then previous one
			if (hit.t < t){
				colorOfHit = hit.dest->getAmbientColor();
				t = hit.t;
				N = hit.normal.normalize();
				V = (ray->origin - (hit.point)).normalize();

				for (int m=0; m < lightSources.size(); m++){
					L_m = (lightSources[m]->getPosition() - (hit.point)).normalize();
					H = (L_m + V) /= ((L_m + V).length());
					dist = (lightSources[m]->getPosition() - (hit.point)).length();
					diffuse = (std::max(0.f,(N.dotProduct(L_m)))) * (lightSources[m]->getId());
					specular = std::max(0.f, N.dotProduct(H));
					intensity = intensity + hit.dest->getMaterialColor(hit.point, diffuse, specular, lightSources[m]->getIs(), dist);
				}
				
				if(ray->raytype==PRIMARY){
					//CHECK FOR REFLECTIONS IF MATERIAL IS REFLECTIVE
					float materialReflectness = hit.dest->getReflectness();
					if(materialReflectness>0){
						R = ray->direction - (2 * ((ray->direction).dotProduct(N)) * N);
						Vec3f noise = (1e-4 * hit.normal);
						Ray* rayMirror = new Ray();
						rayMirror->raytype = SECONDARY;
						rayMirror->origin = hit.point + noise;
						rayMirror->direction = R.normalize();
						Vec3f reflectedColor = materialReflectness * castRay(rayMirror);
						intensity = intensity + reflectedColor;
					}
				}

				// CHECK FOR OBSTRUCTIONS 
				Ray* rayLight = new Ray();
				int lightPositionSampleCount = 100;
				float shadowStrength = 0;
				Vec3f noise = (1e-3 * hit.normal.normalize());
				rayLight->origin = hit.point + noise;

				for(int n=0; n<lightPositionSampleCount; n++){
					Vec3f lightPosSample = lightSources[0]->getPosition();
					rayLight->direction = (lightPosSample - hit.point).normalize();
					float lightDistance = (lightPosSample - hit.point).length();
					if(getClosestIntersectionT(rayLight) >= lightDistance){
						shadowStrength++;
					}
				}
				shadowStrength = shadowStrength/lightPositionSampleCount;
				colorOfHit = (intensity * shadowStrength);
			}
		}
	}
	return colorOfHit;


}

float Scene::getClosestIntersectionT(Ray* ray){
	float closestT = INFINITY;
	bool hasMissed = true;

	// for now assuming 1 lightsource
	for (int i=0; i < sceneShapes.size(); i++){
		Hit h = sceneShapes[i]->intersect(ray);
		if(h.t > 0 && h.t < closestT){
			closestT = h.t;
			hasMissed = false;
		}
	}

	return closestT;
}


} 
//namespace rt
