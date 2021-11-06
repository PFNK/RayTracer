/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

    TriMesh::TriMesh():Shape(){}
    TriMesh::~TriMesh(){}

    Vec3f TriMesh::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
        return material->getColor(diffuse, specular, is, dist, Vec2f(-1,-1));
    }


    Hit TriMesh::intersect(Ray* ray){
        float smallestT = INFINITY;
        Vec3f bestNormal = Vec3f(0,0,0);
        Vec3f bestPoint = Vec3f(0,0,0);
        bool hitBool = false;

        for(int i=0;i<faces.size();i++){
            Hit tmp = faces[i]->intersect(ray);
            
            if(tmp.t > 0){
            if(tmp.t<smallestT){
                hitBool = true;
                smallestT = tmp.t;
                bestNormal = tmp.normal;
                bestPoint = tmp.point;
            }
            } 
        }

        if(!hitBool){
            Hit h;
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            h.dest = this;
            return h;
        }
        
        Hit hit;
        hit.dest = this;
        hit.point = bestPoint;
        hit.normal = bestNormal;
        hit.t = smallestT;

        return hit;
    } 


} //namespace rt


