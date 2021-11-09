/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"


namespace rt{

    BVH::BVH():Shape(){}

    BVH::BVH(std::vector<Shape*> shapes){
        root = new Node();
        if(shapes.size() > 0){
            printf("Splitting %d shapes in the BVH... \n", shapes.size());
            root=buildTree(shapes, 0);
        }
        else{
            printf("Must have shapes \n");
            root->left = nullptr;
            root->right = nullptr;
            std::vector<Shape*> emptyVector;
            root->shapesStored = emptyVector;
        }
    };

    BVH::~BVH(){}

    Hit BVH::intersect(Ray* ray){
        if(!root->left && !root->right){
            printf("empty root, error maybe? \n");
            Hit h;
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            h.normal = Vec3f(0,0,0);
            h.dest = nullptr;
            return h;
        }

        Hit h = intersectTree(root, ray);
        return h;
    }

    Hit BVH::intersectTree(Node* node, Ray* ray){
        if(node->isEmpty){
            Hit miss;
            miss.point = Vec3f(-1,-1,-1);
            miss.t = 0;
            miss.normal = Vec3f(0,0,0);
            return miss;
        }

        if(!node->isInner){
            Vec3f bestNormal = Vec3f(0,0,0);
            Vec3f bestPoint = Vec3f(0,0,0);
            bool hitBool = false;
            bool hasMissed = true;
            float closestT = INFINITY;
            Shape * shapePointer;

            for(int i=0;i<node->shapesStored.size();i++){
                Hit h = node->shapesStored[i]->intersect(ray);
                if(h.t>0 && h.t<closestT){
                    bestNormal = h.normal;
                    bestPoint = h.point;
                    hasMissed = false;
                    closestT = h.t;
                    shapePointer = h.dest;
                }
            }
            if(hasMissed){
                Hit miss;
                miss.t = 0;
                miss.point = Vec3f(-1,-1,-1);
                miss.dest = nullptr;
                return miss;
            }

            Hit closestHit;
            closestHit.dest = shapePointer;
            closestHit.point = bestPoint;
            closestHit.normal = bestNormal;
            closestHit.t = closestT;
            return closestHit;
        } 

        else{
            Hit hLeft, hRight;
            hLeft.t = hRight.t = INFINITY;
            bool hasMissed = true;
            hLeft.point = hRight.point = Vec3f(-1,-1,-1);
            hLeft.normal = hRight.normal = Vec3f(0,0,0);

            if(node->left){
                if(node->left->bounds.intersect(ray)){
                    hasMissed = false;
                    hLeft = intersectTree(node->left, ray);
                }
            }
            
            if(node->right){
                if(node->right->bounds.intersect(ray)){
                    hasMissed = false;
                    hRight = intersectTree(node->right, ray);
                }
            }

            Hit miss;
            miss.point = Vec3f(-1,-1,-1);
            miss.t = 0;
            miss.normal = Vec3f(0,0,0);

            if(hasMissed) return miss;

            if(hLeft.t <= 0){
                if(hRight.t > 0 && hRight.t != INFINITY) return hRight;
                return miss;
            }
            
            if(hRight.t <= 0){
                if(hLeft.t > 0 && hLeft.t != INFINITY) return hLeft;
                return miss;
            }

            if(hRight.t<=hLeft.t) return hRight;
            if(hLeft.t<=hRight.t) return hLeft;

            return miss;
        }
    }

    BVH::Node* BVH::buildTree(std::vector<Shape*> shapes, int attempts){
        if(shapes.size()==0){
            Node* emptyNode = new Node();
            Bounds emptyBounds;
            std::vector<Shape*> emptyShapes;
            emptyNode->bounds = emptyBounds;
            emptyNode->left = nullptr;
            emptyNode->right = nullptr;
            emptyNode->isInner = false;
            emptyNode->shapesStored = emptyShapes;
            emptyNode->isEmpty = true;
            return emptyNode;
        }

        if(shapes.size()==1 || attempts>=MAX_SPLIT_ATTEMPTS){
            Node* leaf = new Node();
            Bounds totalBound = shapes[0]->getBounds();
            
            for(int i=0;i<shapes.size();i++){
                totalBound = Bounds::boundsUnion(totalBound, shapes[i]->getBounds());
                leaf->shapesStored.push_back(shapes[i]);
            }
            leaf->bounds = totalBound;
            leaf->left = nullptr;
            leaf->right = nullptr;
            leaf->isInner = false;
            leaf->isEmpty = false;
            return leaf;
        }

        else{
            Node* innerNode = new Node();
            std::vector<Shape*> leftChildren;
            std::vector<Shape*> rightChildren;
            Bounds totalBound = shapes[0]->getBounds();
            innerNode->isInner = true;
            std::vector<Shape*> emptyShapes;
            innerNode->shapesStored = emptyShapes;
            innerNode->isEmpty = false;
            
            for(int i=1;i<shapes.size();i++){
                totalBound = Bounds::boundsUnion(totalBound, shapes[i]->getBounds());
            }

            innerNode->bounds = totalBound;
            int splitAxIndex = totalBound.getBoundsSplitIndex();
            Vec3f midPoint = totalBound.min + ((totalBound.max - totalBound.min) * 0.5).length();
            
            for(int i=0;i<shapes.size();i++){
                Bounds shapeBound = shapes[i]->getBounds();
                Vec3f shapeCentroid = shapeBound.min + ((shapeBound.max - shapeBound.min) * 0.5).length();
                if(shapeCentroid[splitAxIndex] < midPoint[splitAxIndex]) leftChildren.push_back(shapes[i]);
                else rightChildren.push_back(shapes[i]);
            }
            // printf("left children size %d \n", leftChildren.size());
            // printf("right children size %d \n", rightChildren.size());
            if(leftChildren.size() == 0 || rightChildren.size() == 0){
                innerNode->left = buildTree(leftChildren, attempts+1);
                innerNode->left = buildTree(leftChildren, attempts+1);
            } 
            else{
                innerNode->left = buildTree(leftChildren, 0);
                innerNode->right = buildTree(rightChildren, 0);
            }

            return innerNode;

        }
    }


    Vec3f BVH::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){
        printf("this should never be called! \n");
    };



} //namespace rt


