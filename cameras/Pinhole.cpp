/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"
// #include "core/RayHitStructs.h"



namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(width, height, fov, position, lookat, up){
		Vec3f zaxis = lookat.normalize();                // forward
    	Vec3f xaxis = ((up.normalize()).crossProduct(zaxis)).normalize();   // right
    	Vec3f yaxis = xaxis.crossProduct(zaxis).normalize();                            // up

		// Vec3f zaxis = (this->position - lookat).normalize();                // forward
    	// Vec3f xaxis = (zaxis.crossProduct(up.normalize())).normalize();     // right
    	// Vec3f yaxis = -zaxis.crossProduct(xaxis);    
		// x t_x
		// y t_y
		// z t_z
		// 0 1

		cameraToWorld = Matrix44f(
			xaxis[0], xaxis[1], xaxis[2], position[0],
			yaxis[0], yaxis[1], yaxis[2], position[1],
			zaxis[0], zaxis[1], zaxis[2], position[2],
			0.0, 0.0, 0.0, 1.0);

	}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	Ray* Pinhole::getPrimaryRay(int pixel_x, int pixel_y){
		float normalized_x = (pixel_x + 0.5) / width;
		float normalized_y = (pixel_y + 0.5) / height;
		float ratio = (float)width / height;
		float fovInRad = this->fov * (M_PI/180);
		float cameraPixel_x = (2 * normalized_x - 1) * ratio * tan(fovInRad/2);
		float cameraPixel_y = (1 - 2 * normalized_y) * tan(fovInRad/2);

		Vec3f directionCameraSpace(cameraPixel_x, cameraPixel_y, -1);
		Vec3f originCameraSpace(0, 0, 0);
		
		Vec3f originWorldSpace, directionWorldSpace;
		cameraToWorld.multVecMatrix(originCameraSpace, originWorldSpace);
		cameraToWorld.multDirMatrix(directionCameraSpace, directionWorldSpace);

		// finally vector from origin in the direction in world space
		Vec3f direction = directionWorldSpace - originWorldSpace; 

		Ray* ray = new Ray();
		ray->raytype = PRIMARY;
		ray->origin = this->position;
		ray->direction = direction.normalize();

		return ray;
	}



} //namespace rt

