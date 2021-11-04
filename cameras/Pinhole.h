/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "core/RayHitStructs.h"

namespace rt{

class Pinhole:public Camera{
public:

	//
	// Constructors
	//
	Pinhole();
	Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up);

	//
	//Destructor
	//
	~Pinhole(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
	Ray* getPrimaryRay(int pixel_x, int pixel_y);

	Matrix44f cameraToWorld;
};



} //namespace rt




#endif /* PINHOLE_H_ */
