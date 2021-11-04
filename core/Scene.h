/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"


using namespace rapidjson;

namespace rt{

class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);
	Vec3f castRay(Ray* ray);
	bool checkIntersection(Ray* ray, Vec3f lightPos, Vec3f noise);

	// bool Intersect(const Ray &ray, SurfaceInteraction *isect) const; 
	// - traces the given ray into the scene and returns a Boolean value indicating whether the ray intersected any of the primitives. 
	// - If so, it fills in the provided SurfaceInteraction structure with information about the closest intersection point along the ray.

    // bool IntersectP(const Ray &ray) const;
	// - checks for the existence of intersections along the ray but does not return any information about those intersections, used for shadow rays

    // bool IntersectTr(Ray ray, Sampler &sampler, SurfaceInteraction *isect, Spectrum *transmittance) const;

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;
	Vec3f backgroundColor;

};

} //namespace rt



#endif /* SCENE_H_ */
