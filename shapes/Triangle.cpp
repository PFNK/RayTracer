/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

    Triangle::Triangle():Shape(){}
    Triangle::~Triangle(){}

    Vec3f Triangle::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
        Vec2f uv(-1,-1);;
        if(material->hasTexture){
            // uv(-1,-1);
            // DO TEXTURE MAPPING STUFF
            // get u,v coordinate Vec2f
            uv = Vec2f(-1,-1);
        }
		return material->getColor(diffuse, specular, is, dist, uv);
	}

    Hit Triangle::intersect(Ray* ray){
        Hit h;
        
        Vec3f normal = ((v1 - v0).crossProduct(v2 - v0)).normalize();
        // printf("normal triangle %f %f %f \n ", normal[0],normal[1],normal[2]);

        // if((normal.dotProduct(ray->direction.normalize())) > 0){
        //     normal = -normal;
        // }

        float denom = normal.dotProduct(ray->direction);
        if (abs(denom)<0.0001f){
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            return h;
        }

        // parallel
        // if (n.dotProduct(ray->direction) == 1 || n.dotProduct(ray->direction) == -1){
        //     h.t = 0;
        //     h.point = Vec3f(-1,-1,-1);
        //     return h;
        // }
        
        // // compute d parameter using equation 2
        // float d = n.dotProduct(v0); 
        // // compute t (equation 3)
        // float t = (n.dotProduct(ray->origin) + d) / n.dotProduct(ray->direction); 

        float t = (v0 - (ray->origin)).dotProduct(normal) / denom;
        // printf("t triangle %f \n ", t);

        // printf("triagle t %f \n", t );
        // check if the triangle is in behind the ray
        // if (t <= 0){
        //     h.t = 0;
        //     h.point = Vec3f(-1,-1,-1);
        //     return h;
        // } // the triangle is behind 
    
        // compute the intersection point using equation 1
        h.point = ray->origin + t * ray->direction; 

        // t = (v0 - (ray->origin)).dotProduct(n) / (n.dotProduct(ray->direction));
        // printf("triagle t %f\n", ray->direction[1]);

        // float t = (v0 - (ray->origin)).dotProduct(n) / ((ray->direction).dotProduct(n));
        // printf("triagle t %f\n", t);

        h.t = t;
        h.normal = normal;//(v1 - v0).crossProduct(v2 - v1);
        if((normal.dotProduct(ray->direction.normalize())) > 0){
            h.normal = -h.normal;
        }

        // if(h.normal.dotProduct(ray->direction)<0){
        //     h.normal = -h.normal;
        // }
    
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
