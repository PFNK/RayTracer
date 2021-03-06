/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"
#include "shapes/Bounds.h"
#include "shapes/BVH.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace rt{

class TriMesh: public Shape{

public:

    TriMesh();
    TriMesh(Vec3f center, std::string path, float sizeScale, bool useBVH):center(center), useBVH(useBVH){
        // read the ply file and create triangles
        std::string value;
        ifstream stream(path);

        getline(stream, value);

        while(value.rfind("element", 0) != 0){
            getline(stream, value);
        }

        string elementLine = value.c_str(); 
        int numberIndexStart = elementLine.find_last_of(' ');
        elementLine = elementLine.substr(numberIndexStart, elementLine.length()-1);
        int nVertices = atoi(elementLine.c_str());

        getline(stream, value);

        while(value.rfind("element", 0) != 0){
            getline(stream, value);
        }

        elementLine = value.c_str(); 
        numberIndexStart = elementLine.find_last_of(' ');
        elementLine = elementLine.substr(numberIndexStart, elementLine.length()-1);
        int nFaces = atoi(elementLine.c_str());

        while(value.rfind("end_header", 0) != 0){
            getline (stream, value);
        }

        int i=0;
        float x,y,z,e;

        // apple and beethoven need to be rotated
        Matrix44f rotation = Matrix44f(
			1 , 0, 0, 0,
			0 , 0, 1, 0,
			0, -1, 0, 0,
			0.0, 0.0, 0.0, 1.0);

        while(i<nVertices){
            getline (stream, value);
            istringstream iss(value);
            iss >> x;
            iss >> y;
            iss >> z;
            // Vec3f point((x*sizeScale)+center[0], (y*sizeScale)+center[1], (z*sizeScale)+center[2]);
            Vec3f vertex = Vec3f((x*sizeScale), (y*sizeScale), (z*sizeScale));
            rotation.multVecMatrix(vertex, vertex);
            Vec3f* rotatedVertex = new Vec3f(vertex.x+center[0], vertex.y+center[1], vertex.z+center[2]);
            vertices.push_back(rotatedVertex);
            i++;
        }

        i=0;
        std::vector<Shape*> bvhShapes;

        while(i<nFaces){
            getline (stream, value);
            istringstream iss(value);
            iss >> e;
            iss >> x;
            iss >> y;
            iss >> z;
            Shape* t = new Triangle(vertices[x], vertices[y], vertices[z]);
            bvhShapes.push_back(t);
            i++;
        }
        if(useBVH){
            bvh = new BVH(bvhShapes);
            bvh->material = this->material;
        }
        else{
            faces = bvhShapes;
        }
        //     std::vector<Shape*> bvhShapes;
        //     for(int i=0;i<faces.size();i++) bvhShapes.push_back(faces[i]);
        //     bvh = new BVH(bvhShapes);
        //     bvh->material = this->material;
        // } 

        stream.close(); 
    };

    virtual ~TriMesh();

    Hit intersect(Ray* ray);

    Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

    Bounds getBounds(){
        Bounds b(Vec3f(INFINITY,INFINITY,INFINITY), Vec3f(-INFINITY,-INFINITY,-INFINITY));
        for(int i=0;i<vertices.size();i++){
            b.comparePoint(vertices[i]);
        }
        return b;
    }

private:
    Vec3f center;
    vector<Vec3f*> vertices;
    vector<Shape*> faces; // Shape but is triangle always
    BVH* bvh;
    bool useBVH;

};



} //namespace rt




#endif /* TRIMESH_H_ */
