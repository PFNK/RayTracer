/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"


namespace rt{

    BVH::BVH():Shape(){}

    BVH::BVH(std::vector<Shape*> shapes){
        if(shapes.size() > 0){
            root = new Node();
            root=buildTree(shapes);
        }
        else{
            printf("Must have shapes \n");
            root = new Node();
            root->left = nullptr;
            root->right = nullptr;
            root->shape = nullptr;
        }
    };

    BVH::~BVH(){}

    Hit BVH::intersect(Ray* ray){
        printf("in BVH intersect \n");
        // root->shape = nullptr;
        // printf(root->right == ? "true\n" : "false\n");
        if(root->isInner) printf("root is inner? \n");
        if(!root->left && !root->right){
            printf("empty BVH intersect \n");
            Hit h;
            h.t = 0;
            h.point = Vec3f(-1,-1,-1);
            h.normal = Vec3f(0,0,0);
            h.dest = nullptr;
            return h;
        }
        return intersectTree(root, ray);
    }

    Hit BVH::intersectTree(Node* node, Ray* ray){
        
        if(!node->isInner){
            printf("is a leaf \n");
            return node->shape->intersect(ray);
        } 
        else{
            printf("not a leaf \n");
            Hit hLeft, hRight;
            hLeft.t = hRight.t = INFINITY;
            hLeft.point = hRight.point = Vec3f(-1,-1,-1);
            hLeft.normal = hRight.normal = Vec3f(0,0,0);
            if(node->left->bounds.intersect(ray)){
                printf("here \n");
                hLeft = intersectTree(node->left, ray);
            } 
            if(node->right->bounds.intersect(ray)){
                printf("here \n");
                hRight = intersectTree(node->right, ray);
            }
            printf("here \n");
            if(hLeft.t < hRight.t) return hLeft;
            else return hRight; 
        }
    }

    BVH::Node* BVH::buildTree(std::vector<Shape*> shapes){
        printf("bvh build tree\n");

        // if(shapes.size()==0){
        //     printf("empty leaf\n");
        //     Node* leaf = new Node();
        //     leaf->shape = nullptr;
        //     leaf->left = nullptr;
        //     leaf->right = nullptr;
        //     leaf->isInner = false;
        //     return leaf;
        // }

        if(shapes.size()==1){
            printf("creating leaf \n");
            Node* leaf = new Node();
            leaf->shape = shapes[0];
            leaf->bounds = shapes[0]->getBounds();
            leaf->left = nullptr;
            leaf->right = nullptr;
            leaf->isInner = false;
            return leaf;
        }

        else{
            printf("not leaf\n");
            Node* innerNode = new Node();
            std::vector<Shape*> leftChildren;
            std::vector<Shape*> rightChildren;
            Bounds totalBound = shapes[0]->getBounds();
            innerNode->isInner = true;
            innerNode->bounds = totalBound;
            innerNode->shape = nullptr;
            
            for(int i=1;i<shapes.size();i++){
                totalBound = Bounds::boundsUnion(totalBound, shapes[i]->getBounds());
            }
            int splitAxIndex = totalBound.getBoundsSplitIndex();
            Vec3f midPoint = totalBound.min + ((totalBound.max - totalBound.min) * 0.5).length();
            for(int i=0;i<shapes.size();i++){
                Bounds shapeBound = shapes[i]->getBounds();
                Vec3f shapeCentroid = shapeBound.min + ((shapeBound.max - shapeBound.min) * 0.5).length();
                if(shapeCentroid[splitAxIndex] < midPoint[splitAxIndex]) leftChildren.push_back(shapes[i]);
                else rightChildren.push_back(shapes[i]);
            }
            printf("left children size %d \n", leftChildren.size());
            printf("right children size %d \n", rightChildren.size());

            // if(leftChildren.size() == 1){
            //     printf("returing leaf \n");
            //     Node* leaf = new Node();
            //     leaf->shape = leftChildren[0];
            //     leaf->bounds = leftChildren[0]->getBounds();
            //     leaf->left = nullptr;
            //     leaf->right = nullptr;
            //     innerNode->left = leaf;
            // }
            // else{
                innerNode->left = buildTree(leftChildren);
            // }

            // if(rightChildren.size() == 1){
            //     printf("returing leaf \n");
            //     Node* leafRight = new Node();
            //     leafRight->shape = rightChildren[0];
            //     leafRight->bounds = rightChildren[0]->getBounds();
            //     leafRight->left = nullptr;
            //     leafRight->right = nullptr;
            //     innerNode->right = leafRight;
            // }
            // else{
                innerNode->right = buildTree(rightChildren);
            // }

        }
    }


    Vec3f BVH::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist){};


    



} //namespace rt


