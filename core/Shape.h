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
#include "shapes/Bounds.h"

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

	virtual Bounds getBounds()=0;

	// shape creation 
	static Shape* createShape(Value& shapeSpecs);

	static Shape* createBVH(std::vector<Shape*> shapes);

	virtual Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist)=0;

	Vec3f getAmbientColor() const{
		return material->getAmbientColor();
	}

	float getReflectness() const{
		return material->getReflectness();
	}



public:

	Material * material;

};


} //namespace rt


#endif /* SHAPE_H_ */
