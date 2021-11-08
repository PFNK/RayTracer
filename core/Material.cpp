/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "parsers/PPMWriter.h"


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
        string tPath;
        int tWidth, tHeight = 0;
        vector<Vec3f> texture;

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
            tPath = materialSpecs["tPath"].GetString();
            tWidth = materialSpecs["tWidth"].GetInt();
            tHeight = materialSpecs["tHeight"].GetInt();
            texture = readTexture(tPath, tHeight, tWidth);
        }

        Material* material = new BlinnPhong(ks, kd, kr, specularexponent, diffusecolor, texture, tWidth, tHeight);
        material->hasTexture = materialSpecs.HasMember("tPath");
        return material;

    }

    vector<Vec3f> Material::readTexture(string path, int height, int width){
        vector<Vec3f> pixelbuffer;

        string value;
        path = path.substr(0, path.find_last_of('.')) + ".ppm";
        ifstream stream(path);
        int R, G, B;

        getline (stream, value);
        getline (stream, value);
        getline (stream, value);
        getline (stream, value);

        while (getline (stream, value)) {
            R = stoi(value.c_str());
            getline (stream, value);
            G = stoi(value.c_str());
            getline (stream, value);
            B = stoi(value.c_str());
            pixelbuffer.push_back(Vec3f(R/255.0, G/255.0, B/255.0));
        }

        stream.close(); 
        return pixelbuffer;
    }




} //namespace rt


