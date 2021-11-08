/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_
#include "math/geometry.h"
#include "rapidjson/document.h"

using namespace rapidjson;

        // "type": "pointlight",
        // "position": [0.0, 1.0, 1.5],
        // "is": [100.0, 100.0, 100.0],
        // "id": [100.0, 100.0, 100.0]

namespace rt{

class LightSource{
public:
    //
	// Constructors
	//
	LightSource(){};

	//
	// Destructor
	//
	virtual ~LightSource();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static LightSource* createLightSource(Value& lightSourceSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printLightSource()=0;



	//
	// other LightSource functions (to complete)
	//

    
	//Getters and Setters
	//
	virtual Vec3f getPosition()=0;
	virtual Vec3f getId()=0;
	virtual Vec3f getIs()=0;

};

};



#endif /* LIGHTSOURCE_H_ */
