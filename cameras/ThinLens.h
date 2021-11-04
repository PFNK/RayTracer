/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
// #include "core/RayHitStructs.h"


namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int width, int height, int fov);

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

	Ray* getPrimaryRay(int pixel_x, int pixel_y);

};



} //namespace rt




#endif /* THINLENS_H_ */
