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
		Vec3f zaxis = lookat.normalize();                // forward axis
    	Vec3f xaxis = (zaxis).crossProduct(up.normalize()).normalize();   // to right axis
    	Vec3f yaxis = xaxis.crossProduct(zaxis).normalize();              // up axis

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
		// normalize to be in correct (0,1) range
		float normalized_x = (pixel_x + 0.5) / width;
		float normalized_y = (pixel_y + 0.5) / height;
		float imageRatio = (float)width / height;
		float fovInRad = fov * (M_PI/180);
		// switch to be (-1,1) so that x=0 is in the middle of image
		float cameraPixel_x = (2 * normalized_x - 1) * imageRatio * tan(fovInRad/2);
		float cameraPixel_y = (1 - 2 * normalized_y) * tan(fovInRad/2);

		float Px = (2 * ((pixel_x + 0.5) / width) - 1) * tan(fov / 2 * M_PI / 180); 
		float Py = (1 - 2 * ((pixel_y + 0.5) / height)) * tan(fov / 2 * M_PI / 180); 
		Vec3f direction(Px,Py,1);
		Vec3f worldDirection;
		cameraToWorld.multDirMatrix(direction.normalize(), worldDirection);
		worldDirection = worldDirection.normalize();
		// printf("worldDir: %f %f %f \n", worldDirection.x, worldDirection.y, worldDirection.z);


		// printf("px %f \n", cameraPixel_x);
		// printf("py %f \n", cameraPixel_y);


		// Vec3f pixelCameraSpace = Vec3f(cameraPixel_x, cameraPixel_y, 1).normalize();
		// Vec3f originCameraSpace(0, 0, 0);
		// // transform to the world coordinates 
		// Vec3f originWorldSpace, pixelWorldSpace;
		// cameraToWorld.multVecMatrix(originCameraSpace, originWorldSpace);
		// cameraToWorld.multDirMatrix(pixelCameraSpace, pixelWorldSpace);

		// pixelWorldSpace = pixelWorldSpace.normalize();

		// // printf("worldDir: %f %f %f \n", pixelWorldSpace.x, pixelWorldSpace.y, pixelWorldSpace.z);

		// // finally vector from camera to the pixel in the world space
		// Vec3f directionWorldSpace = pixelWorldSpace;// - originWorldSpace; 
		// printf("Primary ray y coordinate: %f \n", directionWorldSpace[1]);

		// Vec3f direction = directionCameraSpace - originCameraSpace;
		// cameraToWorld.multDirMatrix(direction, direction);

		// float imageAspectRatio = (float)width / height; // assuming width > height 
		// float Px = (2 * ((pixel_x + 0.5) / width) - 1) * tan(fovInRad / 2) * imageAspectRatio; 
		// float Py = (1 - 2 * ((pixel_y + 0.5) / height)) * tan(fovInRad / 2); 
		// Vec3f rayOrigin = Vec3f(0, 0, 0); 
		// Vec3f rayOriginWorld, rayPWorld; 
		// cameraToWorld.multVecMatrix(rayOrigin, rayOriginWorld); 
		// cameraToWorld.multVecMatrix(Vec3f(Px, Py, -1), rayPWorld); 
		// Vec3f rayDirection = rayPWorld - rayOriginWorld; 
		// rayDirection.normalize(); // it's a direction so don't forget to

		// float scale = tan(fov / 2 * M_PI / 180); 
    	// float imageAspectRatio = width / (float)height; 
        // float x = (2 * (pixel_x + 0.5) / (float)width - 1) * imageAspectRatio * scale; 
        // float y = (1 - 2 * (pixel_y + 0.5) / (float)height) * scale; 
		// Vec3f orig;
		// cameraToWorld.multVecMatrix(Vec3f(0), orig); 
		// Vec3f dir; 
        // cameraToWorld.multDirMatrix(Vec3f(x, y, 1), dir); 
        // dir = dir.normalize();
		// Ray* ray = new Ray();
		// ray->raytype = PRIMARY;
		// ray->origin = orig;//this->position;
		// ray->direction = dir;//direction.normalize();
		// printf("Primary ray y coordinate: %f \n", dir[1]);
		// return ray;


		Ray* ray = new Ray();
		ray->raytype = PRIMARY;
		ray->origin = position;//this->position;
		ray->direction = worldDirection;//direction.normalize();
		// printf("Primary ray y coordinate: %f \n", ray->direction[1]);
		return ray;
	}



} //namespace rt

