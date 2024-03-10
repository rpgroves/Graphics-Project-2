#include "transformations.h"
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

ModelViewMatrix::ModelViewMatrix() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);

    modelMatrix = glm::rotate(modelMatrix, (float)50, glm::vec3(0.5f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -15.0f)); // Camera is 5 units back (forward..?) from the origin.
    projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
}

glm::mat4 ModelViewMatrix::getMatrix() {
    return mvpMatrix;
}

void ModelViewMatrix::applyToMesh(Mesh &mesh) {
    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
        mesh.vertices[i].Position = glm::vec3(mvpMatrix * glm::vec4(mesh.vertices[i].Position, 1.0f));
    }
}