/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

namespace rt{

class Triangle: public Shape{

public:

    Triangle();
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2):v0(v0),v1(v1),v2(v2){};

    virtual ~Triangle();

    Hit intersect(Ray* ray);
    Vec3f getNormal(Vec3f point){
        return ((v1 - v0).crossProduct(v2 - v0)).normalize();
    }

private:

    Vec3f v0;
    Vec3f v1;
    Vec3f v2;

};



} //namespace rt




#endif /* TRIANGLE_H_ */
