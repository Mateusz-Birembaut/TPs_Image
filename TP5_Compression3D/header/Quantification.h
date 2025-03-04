
#ifndef QUANTIFICATION_H
#define QUANTIFICATION_H

#include "mesh.h"
#include <cmath>
#include <iostream>
#include <cfloat>
#include <vector>
#include "Eigen/Dense"
#include "BoundingBox.h"

void quantification(int quantification_factor, Mesh &mesh, BoundingBox bb) {
    float range = BoundingBox::getRange(bb);

    float maxQuant = pow(2, quantification_factor) - 1;

    for (Eigen::Vector3f &vertex : mesh.getVertices()) { 

        Eigen::Vector3f quantized = ((vertex - bb.min) * (maxQuant / range)).array().round();

        vertex = quantized;
    }

    mesh.computeGlobalMeshTransform();
}

void dequantification(int quantification_factor, Mesh &mesh, BoundingBox bb) {
    float range = BoundingBox::getRange(bb);

    float maxQuant = pow(2, quantification_factor) - 1;

    for (Eigen::Vector3f &vertex : mesh.getVertices()) { 

        Eigen::Vector3f dequantized = vertex * (range/maxQuant) + bb.min;

        vertex = dequantized; 

    }

    mesh.computeGlobalMeshTransform();
}


#endif 