/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace rt{

class TriMesh: public Shape{

public:

    TriMesh();
    TriMesh(Vec3f center, std::string path, float sizeScale):center(center){
        // read the ply file and create triangles
        Vec3f tmp;

        int index = 0;
        std::string value;
        ifstream stream(path);

        getline(stream, value);

        while(value.rfind("element", 0) != 0){
            getline(stream, value);
        }

        string s = value.c_str(); 
        int m = s.find_last_of(' ');
        s = s.substr(m,s.length()-1);
        int nVertices = atoi(s.c_str());

        getline(stream, value);

        while(value.rfind("element", 0) != 0){
            getline(stream, value);
        }

        s = value.c_str(); 
        m = s.find_last_of(' ');
        s = s.substr(m,s.length()-1);
        int nFaces = atoi(s.c_str());

        while((value.rfind("end_header", 0) != 0)){
            getline (stream, value);
        }
        // printf("Number of vertices: %d, faces %d", nVertices, nFaces);
        int i=0;
        float x,y,z,e;

        while(i<nVertices){
            getline (stream, value);
            istringstream iss(value);
            iss >> x;
            iss >> y;
            iss >> z;
            Vec3f* vertex = new Vec3f((x*sizeScale)+center[0], (y*sizeScale)+center[1], (z*sizeScale)+center[2]);
            vertices.push_back(vertex);
            i++;
        }


        i=0;

        while(i<nFaces){
            getline (stream, value);
            istringstream iss(value);
            iss >> e;
            iss >> x;
            iss >> y;
            iss >> z;
            Triangle* t = new Triangle(vertices[x], vertices[y], vertices[z]);
            faces.push_back(t);
            i++;
        }
        stream.close(); 
        printf("mesh done \n");


    };

    virtual ~TriMesh();

    Hit intersect(Ray* ray);

    Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

private:

    Vec3f center;
    vector<Vec3f*> vertices;
    vector<Triangle*> faces;

};



} //namespace rt




#endif /* TRIMESH_H_ */
