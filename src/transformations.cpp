#include "transformations.h"
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

ModelViewMatrix::ModelViewMatrix() {
    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1.0f);
    // projectionMatrix = glm::mat4(1.0f);

    modelMatrix = glm::rotate(modelMatrix, (float)50, glm::vec3(0.5f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -30.0f)); // Camera is 5 units back (forward..?) from the origin.
    // projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    totalMatrix = viewMatrix * modelMatrix; // = projectionMatrix * viewMatrix * modelMatrix;
}


void ModelViewMatrix::applyToMesh(Mesh &mesh) {
    glm::mat4 totalMatrix = viewMatrix * modelMatrix;
    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
        mesh.vertices[i].Position = glm::vec3(totalMatrix * glm::vec4(mesh.vertices[i].Position, 1.0f));
        mesh.vertices[i].Normal = glm::vec3(totalMatrix * glm::vec4(mesh.vertices[i].Normal, 0.0f)); //TODO: see if this breaks stuff
    }
}

void ModelViewMatrix::scale(float multiplier) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(multiplier, multiplier, multiplier));
    // totalMatrix = viewMatrix * modelMatrix;
}

void ModelViewMatrix::rotate(float angle, glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
    // totalMatrix = viewMatrix * modelMatrix;
}