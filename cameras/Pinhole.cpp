/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"



namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(width, height, fov, position, lookat, up){
		Vec3f zaxis = lookat.normalize(); // forward axis
    	Vec3f xaxis = (zaxis).crossProduct(up.normalize()).normalize(); // to right axis
    	Vec3f yaxis = xaxis.crossProduct(zaxis).normalize();   // up axis

		// x-axis t_x
		// y-axis t_y
		// z-axis t_z
		//    0    1
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
		// normalize and shift to be in correct (-1,1) range where centre of image is (0,0)
		float normalized_x = (pixel_x + 0.5) / width;
		float normalized_y = (pixel_y + 0.5) / height;
		float cameraPixel_x = (2 * normalized_x - 1) * tan(fov/2 * M_PI/180); 
		float cameraPixel_y = (1 - 2 * normalized_y) * tan(fov/2 * M_PI/180);

		Vec3f direction(cameraPixel_x, cameraPixel_y, 1);
		Vec3f worldDirection;
		cameraToWorld.multDirMatrix(direction.normalize(), worldDirection);
		worldDirection = worldDirection.normalize();

		Ray* ray = new Ray();
		ray->raytype = PRIMARY;
		ray->origin = position; // ray origin is camera's position
		ray->direction = worldDirection;
		return ray;
	}



} //namespace rt

