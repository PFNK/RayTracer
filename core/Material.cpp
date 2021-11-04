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
            // Vec3f* pixelbuffer=new Vec3f[tWidth*tHeight];
            // for (int i = 0; i < tWidth*tHeight; ++i) {
		
            //     pixelbuffer[i] = texture[i] * 255;
            // }
            // PPMWriter::PPMWriter(tWidth, tHeight, texture, "./textureTest.ppm");

        }

        Material* material = new BlinnPhong(ks, kd, kr, specularexponent, diffusecolor, texture, tWidth, tHeight);
        material->hasTexture = materialSpecs.HasMember("tPath");
        return material;

    }

    vector<Vec3f> Material::readTexture(string path, int height, int width){
        Vec3f tmp;
        // Vec3f* pixelbuffer=new Vec3f[width*height];
        vector<Vec3f> pixelbuffer;

        int index = 0;
        string value;
        path = path.substr(0, path.find_last_of('.')) + ".ppm";
        ifstream stream(path);
        int R, G, B;

        getline (stream, value);
        getline (stream, value);
        getline (stream, value);
        getline (stream, value);

        while (getline (stream, value)) {
        // for(int i=0;i<(height*width); i++){
            R = stoi(value.c_str());
            getline (stream, value);
            G = stoi(value.c_str());
            getline (stream, value);
            B = stoi(value.c_str());
            pixelbuffer.push_back(Vec3f(R/255.0, G/255.0, B/255.0));
            // index++;
            // printf("pixel R %f, G %f, B %f \n", pixelbuffer[i][0], pixelbuffer[i][1], pixelbuffer[i][2]);
        }

        stream.close(); 
        return pixelbuffer;
    }




} //namespace rt


