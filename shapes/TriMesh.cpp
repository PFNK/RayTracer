/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"
#include <typeinfo>


namespace rt{

    TriMesh::TriMesh():Shape(){}
    TriMesh::~TriMesh(){}

    Vec3f TriMesh::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
        return material->getColor(diffuse, specular, is, dist, Vec2f(-1,-1));
    }


    Hit TriMesh::intersect(Ray* ray){
        // printf("trimesh intersection \n");
        float smallestT = INFINITY;
        Vec3f bestNormal = Vec3f(0,0,0);
        Vec3f bestPoint = Vec3f(0,0,0);
        bool hitBool = false;

        for(int i=0;i<faces.size();i++){
            // printf("triangle i %d \n", i);
            Hit tmp = faces[i]->intersect(ray);
            
            if(tmp.t > 0){
            if(tmp.t<smallestT){
                // printf("h t %f", tmp.t);
                // printf(" point %f %f %f ", tmp.point.x, tmp.point.y, tmp.point.z);
                // printf(" normal %f %f %f \n", tmp.normal.x, tmp.normal.y, tmp.normal.z);
                hitBool = true;
                smallestT = tmp.t;
                bestNormal = tmp.normal;
                bestPoint = tmp.point;
            }
            } 
        }

        // printf("triangle intersection done\n");

        // Hit hit;
        // hit.t = 6.898032;
        // hit.point = Vec3f(-0.281825, 1.127214, 0.445962);
        // hit.normal = Vec3f(-0.577350, 0.577350, 0.577350);

        if(!hitBool){
            Hit h;
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            return h;
        }
        
        Hit hit;
        hit.point = bestPoint;
        hit.normal = bestNormal;
        hit.t = smallestT;

        // printf("returning \n");

        return hit;
    } 


} //namespace rt


