#include "Eigen/Dense"
#include "handleGlut.h"
#include "header/BoundingBox.h"
#include "header/Quantification.h"
#include "header/mesh.h"
#include "mesh.h"
#include "BoundingBox.h"
#include "Quantification.h"

int main(int argc, char **argv)
{
    std::cout << "[C++] : Program Started." << std::endl;

    // --- Args --- //
    if (argc != 2)
    {
        std::cerr << "[USE] : " << argv[0] << " <Mesh.ply>" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        // --- Glut init --- //
        glutInit(&argc, argv);

        // --- GLHandler init --- //
        GLHandler &glHandler = GLHandler::getInstance();

        // --- Mesh --- //
        Mesh meshInit;
        meshInit.loadFromPLY(argv[1]);
        meshInit.setMeshColor(Eigen::Vector3f(0.85, 0.85, 1.0));
        meshInit.setPosition(Eigen::Vector3f(-1.0, 1.0, 0.0));

        Mesh meshResult = meshInit.clone();
        meshResult.setMeshColor(Eigen::Vector3f(0.85, 1.0, 0.85));
        meshResult.setPosition(Eigen::Vector3f(1.0, 1.0, 0.0));

        // --- GL Handler Meshes --- //
        glHandler.addMesh(&meshInit);
        glHandler.addMesh(&meshResult);


        BoundingBox bb = BoundingBox::meshBoundingBox(meshResult);
        BoundingBox::print(bb);

        quantification(5, meshResult, bb);
        dequantification(5, meshResult, bb);

        std::cout << RMSE(meshInit, meshResult) << std::endl;

        // --- 3D Compression --- //
        // meshInit && meshResult available for manipulation and linked to glHandler

        // --- Save && Check --- //
        meshResult.saveToPLY("output.ply");

        // --- Run glHandler --- //
        glHandler.run(1600, 900, "TP5 - Compression3D [HAI819I]");

        return EXIT_SUCCESS;
    }

    std::cout << "[C++] : Program Ended." << std::endl;
}