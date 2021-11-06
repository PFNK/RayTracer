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
            Vec3f bottomEdge = *v1-*v0;
            Vec3f N = bottomEdge.crossProduct(*v2-*v0);
            float area = N.length() / 2;
            float height = 2 * area / bottomEdge.length();

            float width = (*v1-*v2).dotProduct(bottomEdge) / bottomEdge.length();
            if(width<bottomEdge.length()) width = bottomEdge.length();

            Vec3f widthVec = bottomEdge.normalize() * width;
            float heightVec = pow((hitPoint - *v0).length(), 2) - pow(((hitPoint-*v0).dotProduct(bottomEdge) / bottomEdge.length()), 2);
            heightVec = sqrt(heightVec);
            float v = heightVec / height;
            float u = (hitPoint - *v0).dotProduct(widthVec) / widthVec.length();
            u = u /width;
            uv = Vec2f(1-u,v);
        }
		return material->getColor(diffuse, specular, is, dist, uv);
	}

    Hit Triangle::intersect(Ray* ray){
        Hit h;

        Vec3f normal = ((*v1 - *v0).crossProduct(*v2 - *v0)).normalize();

        float denom = normal.dotProduct(ray->direction);
        if (abs(denom)<0.0001f){
            h.normal = (0,0,0);
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            return h;
        }

        float t = (*v0 - (ray->origin)).dotProduct(normal) / denom;
        h.point = ray->origin + t * ray->direction; 
        h.t = t;
        h.normal = normal;
        if((normal.dotProduct(ray->direction.normalize())) > 0){
            h.normal = -h.normal;
        }
    
        Vec3f edge0 = *v1 - *v0; 
        Vec3f edge1 = *v2 - *v1; 
        Vec3f edge2 = *v0 - *v2; 

        if (normal.dotProduct(edge0.crossProduct(h.point - *v0)) > 0 && 
            normal.dotProduct(edge1.crossProduct(h.point - *v1)) > 0 && 
            normal.dotProduct(edge2.crossProduct(h.point - *v2)) > 0){
                return h;
        }else{
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            h.normal = Vec3f(0,0,0);
            return h;
        }
    }


} //namespace rt
