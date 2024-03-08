#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    //glm::vec2 TexCoords;
};

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
        this->vertices = vertices;
        this->indices = indices;
    }

    //void Draw(Shader &shader);


private:
    // data for rendering
    unsigned int VAO, VBO /* EBO */;
    void setupMesh();

};

// void Mesh::Draw(Shader &shader) {
//     glBindVertexArray(VAO);
//     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//     glBindVertexArray(0);
// }

void setupMesh() {
    // reads the vertices and indices from the vectors and sets up the VAO, VBO, and EBO
}

