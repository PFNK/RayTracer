/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"
#include "rapidjson/document.h"
#include <vector>
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

    virtual Vec3f getColor(Vec3f diffuse, float specular, Vec3f is, float dist, Vec2f uv)=0;
	virtual Vec3f getAmbientColor()=0;
	virtual float getReflectness()=0;

	static std::vector<Vec3f> readTexture(std::string path, int height, int width);

	
	// Vec3f getAmbientColor(){
	// 	return diffusecolor;
	// }


public:
    bool hasTexture;
};


} //namespace rt



#endif /* MATERIAL_H_ */
