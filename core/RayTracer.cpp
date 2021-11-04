/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include <iterator>

namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){

	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];
	int index = 0;

	//----------main rendering function to be filled------
	for (int j = 0; j < camera->getHeight(); ++j) { 
		for (int i = 0; i < camera->getWidth(); ++i) { 
			Ray* ray = camera->getPrimaryRay(i, j); // dir
			// printf("%f %f %f \n", ray->direction[0], ray->direction[1], ray->direction[2]);
			Vec3f color = scene->castRay(ray);
			pixelbuffer[index] = color;
            // *(pix++) = castRay(orig, dir, objects, lights, options, 0);
			index++; 
		} 
	} 

	return pixelbuffer;

}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, Camera* camera){
	// //---------tonemapping function to be filled--------
	printf("pixelbuffer size %i \n", camera->getWidth()*camera->getHeight());
	float max=0;
	for (int i = 0; i < camera->getWidth()*camera->getHeight(); ++i) {
		// pixelbuffer[i] = pixelbuffer[i] * 255;
		if(pixelbuffer[i][0] > max){
			max = pixelbuffer[i][0];
		}
		if(pixelbuffer[i][1] > max){
			max = pixelbuffer[i][1];
		}
		if(pixelbuffer[i][2] > max){
			max = pixelbuffer[i][2];
		}
	}
	for (int i = 0; i < camera->getWidth()*camera->getHeight(); ++i) {
		
		pixelbuffer[i] = (pixelbuffer[i]/=max) * 255;
	}






	return pixelbuffer;

}





} //namespace rt


