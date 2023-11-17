#include "triangle.h"
#include <iostream>
#include <glm/glm.hpp>

Triangle::Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2, Material* material)
    : Object(material) {
    vertex0 = v0;
    vertex1 = v1;
    vertex2 = v2;
    isSolid = true;
}

bool Triangle::intersect(Ray& ray) const {
    const Vector3D& rayOrigin = ray.getOrigin();
    const Vector3D& rayDirection = ray.getDirection();

    glm::mat3 coefficientMatrix{
        vertex0[0] - vertex1[0], vertex0[0] - vertex2[0], rayDirection[0],
        vertex0[1] - vertex1[1], vertex0[1] - vertex2[1], rayDirection[1],
        vertex0[2] - vertex1[2], vertex0[2] - vertex2[2], rayDirection[2]
    };

    double determinantCoefficient = glm::determinant(coefficientMatrix);

    if (determinantCoefficient == 0) {
        // The ray is parallel to the triangle plane.
        return false;
    }

    glm::mat3 betaDeterminantMatrix{
        vertex0[0] - rayOrigin[0], vertex0[0] - vertex2[0], rayDirection[0],
        vertex0[1] - rayOrigin[1], vertex0[1] - vertex2[1], rayDirection[1],
        vertex0[2] - rayOrigin[2], vertex0[2] - vertex2[2], rayDirection[2]
    };

    glm::mat3 gammaDeterminantMatrix{
        vertex0[0] - vertex1[0], vertex0[0] - rayOrigin[0], rayDirection[0],
        vertex0[1] - vertex1[1], vertex0[1] - rayOrigin[1], rayDirection[1],
        vertex0[2] - vertex1[2], vertex0[2] - rayOrigin[2], rayDirection[2]
    };

    glm::mat3 tDeterminantMatrix{
        vertex0[0] - vertex1[0], vertex0[0] - vertex2[0], vertex0[0] - rayOrigin[0],
        vertex0[1] - vertex1[1], vertex0[1] - vertex2[1], vertex0[1] - rayOrigin[1],
        vertex0[2] - vertex1[2], vertex0[2] - vertex2[2], vertex0[2] - rayOrigin[2]
    };

    double beta = glm::determinant(betaDeterminantMatrix) / determinantCoefficient;
    double gamma = glm::determinant(gammaDeterminantMatrix) / determinantCoefficient;
    double t = glm::determinant(tDeterminantMatrix) / determinantCoefficient;

    
        
    Vector3D norm = crossProduct(vertex1-vertex0,vertex2-vertex0);
    norm.normalize();

    if (beta > 0 && gamma > 0 && (beta + gamma) < 1 && t > 0) {
        ray.setParameter(t, this);
        ray.setNormal(norm);
        return true;
    }

    return false;
}
