/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"


namespace rt{

    Material::~Material(){};

    /**
     * Factory function that returns Material subclass based on shape specifications
     *
     * @param materialSpecs material specifications json object
     *
     * @return Material subclass instance
     *
     */
    Material* Material::createMaterial(Value& materialSpecs){
        float ks = 0, kd = 0, kr = 0, specularexponent = 0;
        Vec3f diffusecolor(0,0,0);
        // std::string tPath;
        int tWidth, tHeight = 0;
            // "ks": 0.6,
            // "kd": 1.0,
            // "specularexponent": 10,
            // "diffusecolor": [1.0, 0.2, 0.2]

        if (materialSpecs.HasMember("ks")){
            ks = materialSpecs["ks"].GetFloat();
        }
        if (materialSpecs.HasMember("kd")){
            kd = materialSpecs["kd"].GetFloat();
        }
        if (materialSpecs.HasMember("kr")){
            kr = materialSpecs["kr"].GetFloat();
        }
        if (materialSpecs.HasMember("specularexponent")){
            specularexponent = materialSpecs["specularexponent"].GetFloat();
        }
        if (materialSpecs.HasMember("diffusecolor")){
            diffusecolor = Vec3f(materialSpecs["diffusecolor"][0].GetFloat(), materialSpecs["diffusecolor"][1].GetFloat(), materialSpecs["diffusecolor"][2].GetFloat());
        }
        if (materialSpecs.HasMember("tPath")){
            std::string tPath = materialSpecs["tPath"].GetString();
        }
        if (materialSpecs.HasMember("tWidth")){
            tWidth = materialSpecs["tWidth"].GetInt();
        }
        if (materialSpecs.HasMember("tHeight")){
            tHeight = materialSpecs["tHeight"].GetInt();
        }

        return new BlinnPhong(ks, kd, kr, specularexponent, diffusecolor);


    }




} //namespace rt


