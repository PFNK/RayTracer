/*
 * Bounds.cpp
 *
 *
 */
#ifndef BOUNDS_H_
#define BOUNDS_H_

#include "math/geometry.h"
#include <vector>
#include <iostream>
#include "core/RayHitStructs.h"


namespace rt{

class Bounds 
{ 
public: 

    Vec3f min;
    Vec3f max; 

    Bounds(const Vec3f minV, const Vec3f maxV) 
    { 
        min = minV; 
        max = maxV; 
    }

    Bounds() 
    { 
        min = Vec3f(0,0,0); 
        max = Vec3f(0,0,0);
    }

    bool intersect(Ray* ray){
        
        float tMin_x = (min.x - ray->origin.x) / ray->direction.x; 
        float tMax_x = (max.x - ray->origin.x) / ray->direction.x;  
        float tMin_y = (min.y - ray->origin.y) / ray->direction.y;
        float tMax_y = (max.y - ray->origin.y) / ray->direction.y;
        float tMin_z = (min.z - ray->origin.z) / ray->direction.z;
        float tMax_z = (max.z - ray->origin.z) / ray->direction.z;
        
        float tmp;

        if (tMin_x > tMax_x){
            std::swap(tMin_x, tMax_x);
        }
        if (tMin_y > tMax_y){
            std::swap(tMin_y,tMax_y);
        }
        if (tMin_z > tMax_z){
            std::swap(tMin_z, tMax_z);
        }
        printf("bounds intersect \n");
        // mins < other maxs
        if(tMin_x > tMax_y || tMin_x > tMax_z) return false;
        if(tMin_y > tMax_x || tMin_y > tMax_z) return false;
        if(tMin_z > tMax_x || tMin_z > tMax_y) return false;

        return true;

    }


    int getBoundsSplitIndex(){
        Vec3f mid = (max - min) * 0.5;
        if(mid[0] > mid[1] && mid[0] > mid[2]) return 0;
        if(mid[1] > mid[0] && mid[1] > mid[2]) return 1;
        return 2;
    }

    void comparePoint(Vec3f* point){
        if(point->x < min.x){
            min.x = point->x;
        }else if(point->x > max.x){
            max.x = point->x;
        }

        if(point->y < min.y){
            min.y = point->y;
        }else if(point->y > max.y){
            max.y = point->y;
        }

        if(point->z < min.z){
           min.z = point->z;
        }else if(point->z > max.z){
            max.z = point->z;
        }
    }

    static Bounds boundsUnion(Bounds b1, Bounds b2){
        float minVal_x = std::min(b1.min.x, b2.min.x);
        float minVal_y = std::min(b1.min.y, b2.min.y);
        float minVal_z = std::min(b1.min.z, b2.min.z);
        float maxVal_x = std::max(b1.max.x, b2.max.x);
        float maxVal_y = std::max(b1.max.y, b2.max.y);
        float maxVal_z = std::max(b1.max.z, b2.max.z);
        return Bounds(Vec3f(minVal_x, minVal_y, minVal_z), Vec3f(maxVal_x, maxVal_y, maxVal_z));
    }
}; 




} //namespace rt



#endif /* BOUNDS_H_ */
