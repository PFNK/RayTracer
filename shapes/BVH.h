/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include "core/Shape.h"
#include <vector>
#include <iostream>


namespace rt{

class BVH: public Shape{

public:

    struct Node{
        Bounds bounds;
        Node* left;
        Node* right;
        std::vector<Shape*> shapesStored;
        bool isInner;
        bool isEmpty;
    };

    BVH();

    BVH(std::vector<Shape*> shapes);

    virtual ~BVH();

    Node* buildTree(std::vector<Shape*> shapes, int attempts);

    Hit intersect(Ray* ray);

    Vec3f getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist);

    Hit intersectTree(Node* node, Ray* ray);

    Bounds getBounds(){
        return root->bounds;
	}

private:
    Node* root;
    int MAX_SPLIT_ATTEMPTS=1;
};



} //namespace rt



#endif /* BVH_H_ */
