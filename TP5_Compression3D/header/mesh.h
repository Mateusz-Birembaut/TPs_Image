#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#include <GL/glut.h>

#include "Eigen/Dense"
#include "happly.h"


class Mesh
{
private:
    // Local
    std::vector<Eigen::Vector3f> vertices_;
    std::vector<Eigen::Vector3f> normals_;
    std::vector<std::array<unsigned int, 3>> triangles_;

    // Global
    Eigen::Affine3f transform_;
    std::vector<Eigen::Vector3f> global_vertices_;
    std::vector<Eigen::Vector3f> global_normals_;

    // Draw
    bool canDraw_;
    Eigen::Vector3f meshColor_ = Eigen::Vector3f(0.8f, 0.8f, 1.0f);

    // Utils
    void computeNormals();


public:
    // Constructor / Clone
    Mesh();
    Mesh clone() const;

    // Imports / Exports
    void loadFromPLY(const char *filename);
    void saveToPLY(const char *filename);

    // Draw
    void setMeshColor(const Eigen::Vector3f &color);
    void draw(bool displayNormals) const;

    //Utils 
    void computeGlobalMeshTransform();

    // Transformations
    void setPosition(const Eigen::Vector3f &position);
    void setRotation(float angle, const Eigen::Vector3f &axis);
    void setScale(const Eigen::Vector3f &scale);
    void setTransform(const Eigen::Affine3f &transform);
    void translate(const Eigen::Vector3f &translation);
    void rotate(float angle, const Eigen::Vector3f &axis);

    

    std::vector<Eigen::Vector3f> & getVertices(){ return vertices_;};

    void quantification(int quantification_factor);
    
};


static float RMSE(Mesh & m1, Mesh & m2){
    std::vector<Eigen::Vector3f> verticesM1 = m1.getVertices();
    std::vector<Eigen::Vector3f> verticesM2 = m2.getVertices();

    int nb_vertices = verticesM1.size();

    float summ = 0;
    for (int i=0; i < nb_vertices; i++) {
        Eigen::Vector3f vertexM1 = verticesM1[i];
        Eigen::Vector3f vertexM2 = verticesM2[i];

        summ += pow((vertexM1[1] - vertexM2[1]), 2);
    }

    float result =  sqrt( (1.0f/nb_vertices) * summ);
    std::cout<< result << std::endl;

    return result;
}


#endif // MESH_H