#include <GL/glew.h>
#include <glm/glm.hpp>
class Mesh;

class ModelViewMatrix {
public:
        glm::mat4 modelMatrix; // Transforms from model space to world space
        glm::mat4 viewMatrix; // Transforms from world space to camera space
        glm::mat4 projectionMatrix; // Transforms from camera space to screen space

        glm::mat4 mvpMatrix; // ModelViewProjection matrix, composition of above 3
        
        ModelViewMatrix();
        glm::mat4 getMatrix();
        void applyToMesh(Mesh &mesh);
};