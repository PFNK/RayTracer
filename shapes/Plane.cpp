/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"


namespace rt{

    Plane::Plane():Shape(){}
    Plane::~Plane(){}

    Vec3f Plane::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
        Vec2f uv(-1,-1);
        if(material->hasTexture){
            float projection_u = (hitPoint - v3).dotProduct(v2-v3) / (v2-v3).length();
            float u = projection_u / (v2-v3).length(); 
            float projection_v = (hitPoint - v3).dotProduct(v0-v3) / (v0-v3).length();
            float v = projection_v / (v0-v3).length();
            uv = Vec2f(u,1-v);
		}
		return material->getColor(diffuse, specular, is, dist, uv);
	}


	/**
	 * Computes whether a ray hit the specific instance of a Plane shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Plane::intersect(Ray* ray){
		Hit h;
		float t;
        h.dest = this;
		//-----------to be implemented -------------
        // want find t where (ray_o + ray_dir * t - v0) * n = 0
        // meaning there is a point along the ray (p=ray_o + ray_dir*t) that lies on the plane (p-v0 dot n = 0) => (p-v0) is perpendicular to normal of plane
        // plugging in p and rearranging for t we get: (v0−ray_o) dot n / ray_dir dot n -> need to check for div by 0 (when ray_dir is parallel to n)
        Vec3f normal = ((v1-v0).crossProduct(v3-v0)).normalize();
        float tDenominator = normal.dotProduct(ray->direction);
        if (abs(tDenominator) < 1e-4){ // almost zero
            h.point = Vec3f(-1,-1,-1); // Miss
            h.t = 0;
            return h;
        }
    
        t = (v0 - (ray->origin)).dotProduct(normal) / tDenominator;
        h.point = ray->origin + t*(ray->direction);
        h.t = t;
        h.normal = -normal;

        // if(h.normal.dotProduct(ray->direction)>0){
        //     h.normal = -h.normal;
        // }

        Vec3f edge0 = v1 - v0; 
        Vec3f edge1 = v2 - v1;
        Vec3f edge2 = v3 - v2;  
        Vec3f edge3 = v0 - v3; 

        if (normal.dotProduct(edge0.crossProduct(h.point - v0)) > 0 && 
            normal.dotProduct(edge1.crossProduct(h.point - v1)) > 0 && 
            normal.dotProduct(edge2.crossProduct(h.point - v2)) > 0 &&
            normal.dotProduct(edge3.crossProduct(h.point - v3)) > 0){
                return h;
        }else{
            h.point = Vec3f(-1,-1,-1); // Miss
            h.t = 0;
            h.normal = Vec3f(0,0,0);
            return h; 
        }

	}



} //namespace rt


