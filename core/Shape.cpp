/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "shapes/BVH.h"

namespace rt{

    Shape::~Shape(){};


    /**
     * Factory function that returns shape subclass based on shape specifications
     *
     * @param shapeSpecs camera specifications json object
     *
     * @return shape subclass instance
     *
     */
    Shape* Shape::createShape(Value& shapeSpecs){

        //check if cameratype is defined
        if(!shapeSpecs.HasMember("type")){
            std::cerr<<"Shape type not specified"<<std::endl;
            exit(-1);
        }

        // Material* material = new Material();

        std::string shapeType=shapeSpecs["type"].GetString();

        //return shape object based on shape specs
        if(shapeType.compare("sphere")==0){
            std::printf("Creating sphere...\n");
            Sphere* sphere = new Sphere(
                Vec3f(shapeSpecs["center"][0].GetFloat(), shapeSpecs["center"][1].GetFloat(), shapeSpecs["center"][2].GetFloat()), 
                shapeSpecs["radius"].GetFloat());

            sphere->material = Material::createMaterial(shapeSpecs["material"]);
            // std::printf("Center %f %f %f...\n", sphere->center[0], sphere->center[1], sphere->center[2]);
            return sphere;
        }

        else if(shapeType.compare("plane")==0){
            std::printf("Creating plane...\n");

            Vec3f v0(shapeSpecs["v0"][0].GetFloat(), shapeSpecs["v0"][1].GetFloat(), shapeSpecs["v0"][2].GetFloat());
            Vec3f v1(shapeSpecs["v1"][0].GetFloat(), shapeSpecs["v1"][1].GetFloat(), shapeSpecs["v1"][2].GetFloat());
            Vec3f v2(shapeSpecs["v2"][0].GetFloat(), shapeSpecs["v2"][1].GetFloat(), shapeSpecs["v2"][2].GetFloat());
            Vec3f v3(shapeSpecs["v3"][0].GetFloat(), shapeSpecs["v3"][1].GetFloat(), shapeSpecs["v3"][2].GetFloat());
            // printf("%f %f %f", n[0],n[1],n[2]);
            Plane* plane = new Plane(v0, v1, v2, v3);
            plane->material = Material::createMaterial(shapeSpecs["material"]);
            return plane;
        }

        else if(shapeType.compare("triangle")==0){
            std::printf("Creating triangle...\n");
            Vec3f* v0 = new Vec3f(shapeSpecs["v0"][0].GetFloat(), shapeSpecs["v0"][1].GetFloat(), shapeSpecs["v0"][2].GetFloat());
            Vec3f* v1 = new Vec3f(shapeSpecs["v1"][0].GetFloat(), shapeSpecs["v1"][1].GetFloat(), shapeSpecs["v1"][2].GetFloat());
            Vec3f* v2 = new Vec3f(shapeSpecs["v2"][0].GetFloat(), shapeSpecs["v2"][1].GetFloat(), shapeSpecs["v2"][2].GetFloat());
            Triangle* triangle = new Triangle(v0, v1, v2);
            triangle->material = Material::createMaterial(shapeSpecs["material"]);
            return triangle;
        }

        else if(shapeType.compare("trimesh")==0){
            std::printf("Creating trimesh...\n");
            Vec3f center = Vec3f(shapeSpecs["center"][0].GetFloat(), shapeSpecs["center"][1].GetFloat(), shapeSpecs["center"][2].GetFloat());
            std::string path = shapeSpecs["plyPath"].GetString();
            float sizeScale = shapeSpecs["sizeScale"].GetFloat();
            TriMesh* mesh = new TriMesh(center, path, sizeScale);
            mesh->material = Material::createMaterial(shapeSpecs["material"]);
            return mesh;

        }


        return 0;

    }

    Shape* Shape::createBVH(std::vector<Shape*> shapes){
        return new BVH(shapes);
    }




} //namespace rt

