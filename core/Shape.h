/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Material.h"

using namespace rapidjson;

namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape(){};

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape();

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray*)=0;

	// virtual Vec3f getNormal(Vec3f point)=0;

	// shape creation 
	static Shape* createShape(Value& shapeSpecs);

	// Vec3f getMaterialColor(Vec3f diffuse, float specular, Vec3f is, float dist) const{
	// 	return material->getColor(diffuse, specular, is, dist, );
	// }

	virtual Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist)=0;

	Vec3f getAmbientColor() const{
		return material->getAmbientColor();
	}

	float getReflectness() const{
		return material->getReflectness();
	}



protected:

	Material * material;

};


} //namespace rt


#endif /* SHAPE_H_ */
