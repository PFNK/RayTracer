/*
 * Scene.cpp
 *
 */
// #define _USE_MATH_DEFINES

#include "Scene.h"
#include "shapes/Sphere.h"
#include <cmath>


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

	//iterate through shapes
	std::cout<<"'shapes' contains "<<jsonShapes.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < jsonShapes.Size(); i++){ // Retrieve values through GetXXX() functions
	        printf("shapes[%d] = %s \n", i, jsonShapes[i].GetObject()["type"].GetString());
			// TODO: create the objects and save to the shapes parameters
			Shape* p = Shape::createShape(jsonShapes[i]);
			// printf("%p \n", &(p->center));
			// shapes.push_back(Shape::createShape(jsonShapes[i]));
			shapes.push_back(p);
	}

	//iterate through lightsources
	std::cout<<"'lightsources' contains "<<jsonLights.Size()<<" elements:"<<std::endl;
	for (SizeType i = 0; i < jsonLights.Size(); i++){ // Retrieve values through GetXXX() functions
	        printf("lightsources[%d] = %s \n", i, jsonLights[i].GetObject()["type"].GetString());
			lightSources.push_back(LightSource::createLightSource(jsonLights[i]));
	}
}

Vec3f Scene::castRay(Ray* ray){
	float t = INFINITY;
	Vec3f colorOfHit = backgroundColor;

	if(ray->raytype==SHADOW){
		Vec3f shadowColor(1,1,1);
		for (int i=0; i < shapes.size(); i++){
			for (int m=0; m < lightSources.size(); m++){
				Hit h = shapes[i]->intersect(ray);
				if(h.t < 0){
					//check if hit is in front of light and not behind
					Vec3f toPoint = h.point - ray->origin;//ray->origin + (-h.t*ray->direction);//h.point - ray->origin;//- h.origin; h.point = ray->origin + (h.t*ray->direction);
					Vec3f toLight = lightSources[m]->getPosition() - ray->origin;
					if(toPoint.length()<=toLight.length()) return Vec3f(0.001,0.001,0.001);
				}
			}
		}
		return Vec3f(1,1,1);
	}
	
	if(ray->raytype==PRIMARY){
	
		for (int i=0; i < shapes.size(); i++){
			Hit hit = shapes[i]->intersect(ray);
			Vec3f intensity(0,0,0);
			Vec3f L_m, N, V, R, H, diffuse;
			float dist, specular;
			
			if (hit.t != 0){
				// if it hits the object and if it is closer hit then previous one
				if (hit.t < t){
					colorOfHit = shapes[i]->getAmbientColor();
					// printf("color %f %f %f \n",colorOfHit[0],colorOfHit[1],colorOfHit[2]);

					N = hit.normal.normalize();
					V = (ray->origin - (hit.point)).normalize();

					for (int m=0; m < lightSources.size(); m++){
						L_m = (lightSources[m]->getPosition() - (hit.point)).normalize();
						H = (L_m + V) /= ((L_m + V).length());
						dist = (lightSources[m]->getPosition() - (hit.point)).length();

						diffuse = (std::max(0.f,(N.dotProduct(L_m)))) * (lightSources[m]->getId());
						specular = std::max(0.f, N.dotProduct(H));

						intensity = intensity + shapes[i]->getMaterialColor(diffuse, specular, lightSources[m]->getIs(), dist);
					}
					
					if(ray->raytype==PRIMARY){
						//CHECK FOR REFLECTIONS
						// IF MATERIAL IS REFLECTIVE
						float materialReflectness = shapes[i]->getReflectness();
						if(materialReflectness>0){
							// printf("REFLECTNESS %f \n",materialReflectness);
							R = ray->direction - (2 * ((ray->direction).dotProduct(N)) * N);
							Vec3f noise = (1e-4 * hit.normal);
							Ray* rayMirror = new Ray();
							rayMirror->raytype = SECONDARY;
							rayMirror->origin = hit.point + noise;
							rayMirror->direction = -R.normalize();
							// rayMirror->bounces = 0;
							Vec3f reflectedColor = materialReflectness * castRay(rayMirror);
							// printf("REFLECTwed %f %f %f \n",reflectedColor[0],reflectedColor[1],reflectedColor[2]);

							intensity = intensity + reflectedColor;
						}
					}
					
					// CHECK FOR OBSTRUCTIONS 
					Ray* rayLight = new Ray();
					rayLight->raytype = SHADOW;
					Vec3f noise = (1e-4 * hit.normal);
					rayLight->origin = hit.point + noise;
					rayLight->direction = (lightSources[0]->getPosition() - (hit.point + noise)).normalize();
					Vec3f shadowColor = castRay(rayLight);

					// if(checkIntersection(rayLight, lightSources[0]->getPosition(), noise)){
					// 	intensity = Vec3f(0.01,0.01,0.01);
					// }

					colorOfHit = (intensity * shadowColor);//colorOfHit + colorOfHit*(intensity.normalize());

					t = hit.t;


					// Vec3f colorGammaCorrected = pow(colorOfHit, Vec3f(1.0 / 2.2));

					// color = material.diffusecolor //ambient
					// for (int m=0; i < lights.size(); i++)
					//    diffuse_val = ((light.position - hit.point).dotProduct(shape.n)) * light.id;
					//    specular_val 
					//    color += material.getColor(diffuse_val, light.is, hit.point-ray.origin);
					//    // IN MAT color += material.kd * (hit.p - light.position dot shape.n) * light.id //diffuse
					//    // IN MAT color += material.ks * (R_m? dot ray.direction)^light.is // specular
				}
			}
		}
		return colorOfHit;
	}

	if(ray->raytype==SECONDARY){
		float t = INFINITY;
		Vec3f colorOfHit = backgroundColor;

		for (int s=0; s < shapes.size(); s++){
			Hit hit = shapes[s]->intersect(ray);
			Vec3f intensity(0,0,0);
			Vec3f L_m, N, V, R, H, diffuse;
			float dist, specular;
			
			if (hit.t != 0){
				if (hit.t < t){
					// printf("SECONDARY HIT \n");
					colorOfHit = shapes[s]->getAmbientColor();
					N = hit.normal.normalize();
					V = (ray->origin - (hit.point)).normalize();
					// printf("color %f %f %f \n",colorOfHit[0],colorOfHit[1],colorOfHit[2]);

					for (int l=0; l < lightSources.size(); l++){
						L_m = (lightSources[l]->getPosition() - (hit.point)).normalize();
						H = (L_m + V) /= ((L_m + V).length());
						dist = (lightSources[l]->getPosition() - (hit.point)).length();

						diffuse = (std::max(0.f,(N.dotProduct(L_m)))) * (lightSources[l]->getId());
						specular = std::max(0.f, N.dotProduct(H));

						colorOfHit = colorOfHit + shapes[s]->getMaterialColor(diffuse, specular, lightSources[l]->getIs(), dist);
					}
					t = hit.t;
				}
			}
		}
		return colorOfHit;
	}

}

bool Scene::checkIntersection(Ray* ray, Vec3f lightPos, Vec3f noise){
	for (int i=0; i < shapes.size(); i++){
		Hit h = shapes[i]->intersect(ray);
		if(h.t < 0){
			//check if hit is in front of light and not behind
			Vec3f toPoint = h.point - ray->origin;//ray->origin + (-h.t*ray->direction);//h.point - ray->origin;//- h.origin; h.point = ray->origin + (h.t*ray->direction);
			Vec3f toLight = lightPos - ray->origin;
			if(toPoint.length()<=toLight.length()) return true;
		}
	}
	return false;
}


} 
//namespace rt
