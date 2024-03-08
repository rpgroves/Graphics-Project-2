#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include "shader_s.h"
#pragma once

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //vector<Texture> textures;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw(Shader &shader);
    unsigned int VAO, VBO, EBO;

private:
    void setupMesh();
};