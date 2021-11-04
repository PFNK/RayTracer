/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

    Triangle::Triangle():Shape(){}
    Triangle::~Triangle(){}

    Hit Triangle::intersect(Ray* ray){
        Hit h;

        // normal to the triangle plane            
        Vec3f normal = ((v1 - v0).crossProduct(v2 - v0)).normalize();

        // if ray and triangle are parallel dot product n * r_dir is 0
        if (normal.dotProduct(ray->direction) == 0){
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            return h;
        }
        
        // SAME AS PLANE, JUST BOUNDS ARE DIFFERENT
        float t = (v0 - (ray->origin)).dotProduct(normal) / ((ray->direction).dotProduct(normal));

        h.point = ray->origin + t * ray->direction;
        h.t = -t;
        h.normal = (v1 - v0).crossProduct(v2 - v1);
        if(h.normal.dotProduct(ray->direction)<0){
            h.normal = -h.normal;
        }
    
        Vec3f edge0 = v1 - v0; 
        Vec3f edge1 = v2 - v1; 
        Vec3f edge2 = v0 - v2; 

        if (normal.dotProduct(edge0.crossProduct(h.point - v0)) > 0 && 
            normal.dotProduct(edge1.crossProduct(h.point - v1)) > 0 && 
            normal.dotProduct(edge2.crossProduct(h.point - v2)) > 0){
                return h;
        }else{
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            h.normal = Vec3f(0,0,0);

            return h;
        }
    }





} //namespace rt
