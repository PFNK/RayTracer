/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"
#include "rapidjson/document.h"
using namespace rapidjson;

namespace rt{

class Material{
public:

    //
	// Constructors
	//
	Material(){};
    // Material(Vec3f diffusecolor):diffusecolor(diffusecolor){};

	//
	// Destructor 
	//
	virtual ~Material();

    static Material* createMaterial(Value& materialSpecs);

    virtual Vec3f getColor(Vec3f diffuse, float specular, Vec3f is, float dist)=0;
	virtual Vec3f getAmbientColor()=0;
	virtual float getReflectness()=0;

	
	// Vec3f getAmbientColor(){
	// 	return diffusecolor;
	// }


// protected:
//     Vec3f diffusecolor;
};


} //namespace rt



#endif /* MATERIAL_H_ */
