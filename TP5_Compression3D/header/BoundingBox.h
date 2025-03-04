
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include <cmath>
#include <iostream>
#include <cfloat>
#include <vector>
#include "Eigen/Dense"
#include "mesh.h"



class BoundingBox {
private:

public:
    Eigen::Vector3f min , max;
    BoundingBox() {}
    BoundingBox( Eigen::Vector3f const & _min , Eigen::Vector3f const & _max )  {
        min = _min;
        max = _max;
    };


    static BoundingBox meshBoundingBox(Mesh & mesh ) {
        BoundingBox box;
        box.min = Eigen::Vector3f(FLT_MAX, FLT_MAX, FLT_MAX); 
        box.max = Eigen::Vector3f(-FLT_MAX, -FLT_MAX, -FLT_MAX); 

        for (const Eigen::Vector3f & vertex : mesh.getVertices()) { 
            box.min[0] = std::min(box.min[0], vertex[0] );
            box.min[1] = std::min(box.min[1], vertex[1]);
            box.min[2] = std::min(box.min[2], vertex[2]);

            box.max[0] = std::max(box.max[0], vertex[0]);
            box.max[1] = std::max(box.max[1], vertex[1]);
            box.max[2] = std::max(box.max[2], vertex[2]);
        }

        return box;
    }


    static float calculateSurfaceArea(const BoundingBox& box) {
        Eigen::Vector3f dimensions = box.max - box.min;
        return 2 * (dimensions[0] * dimensions[1] + dimensions[1] * dimensions[2] + dimensions[2] * dimensions[0]);
    }

    static float getRange(const BoundingBox& box) {
        Eigen::Vector3f point2(box.max[0], box.min[1], box.min[2]);
        float rangeX = (point2 - box.min).norm(); 

        point2 = Eigen::Vector3f(box.min[0], box.max[1], box.min[2]);
        float rangeY = (point2 - box.min).norm();  

        point2 = Eigen::Vector3f(box.min[0], box.min[1], box.max[2]);
        float rangeZ = (point2 - box.min).norm();  

        return fmax(fmax(rangeX, rangeY), rangeZ);
    }


    static void print(const BoundingBox& box){
        std::cout << "Bounding Box:" << std::endl;
        std::cout << "  Min Coordinates: (" 
                << box.min.x() << ", " 
                << box.min.y() << ", " 
                << box.min.z() << ")" << std::endl;
        std::cout << "  Max Coordinates: (" 
                << box.max.x() << ", " 
                << box.max.y() << ", " 
                << box.max.z() << ")" << std::endl;
    }

        

};
#endif 