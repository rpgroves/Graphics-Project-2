#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    setupMesh();
}

void Mesh:: Draw(Shader &shader) {
    // Bind the VAO, draw elements using our indices, and unbind the VAO.
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // Each element is a vertex with all the attributes we got, gets passed through 
    //      whatever shaders are bound, etc.
    glBindVertexArray(0);
}

Mesh Mesh::loadObjFile(const char* filename) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return Mesh(vertices, indices);
    }

    for (std::string line; getline(file, line);) { 
        std::string lineTemp = line;
        if(line != "" && line.at(0) == 'v' && line.at(1) == ' ') {
            Vertex vertex;
            lineTemp = lineTemp.substr(2);
            sscanf(lineTemp.c_str(), "%f %f %f", &vertex.Position.x, &vertex.Position.y, &vertex.Position.z); // huh
            vertex.Color = glm::vec3(1.0f, 0.0f, 0.0f);
            vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
            vertices.push_back(vertex);
        } else if(line != "" && line.at(0) == 'f' && line.at(1) == ' ') {
            unsigned int index1, index2, index3;
            lineTemp = lineTemp.substr(2);
            sscanf(lineTemp.c_str(), "%d %d %d", &index1, &index2, &index3);
            indices.push_back(index1 - 1);
            indices.push_back(index2 - 1);
            indices.push_back(index3 - 1);
        }

        
    }
    for (unsigned int i = 0; i < vertices.size(); i++) {
        std::cout << "Vertex " << i << std::endl;
        std::cout << "\tPosition: " << vertices[i].Position.x << " " << vertices[i].Position.y << " " << vertices[i].Position.z << std::endl;
        std::cout << "\tColor: " << vertices[i].Color.x << " " << vertices[i].Color.y << " " << vertices[i].Color.z << std::endl;
        std::cout << "\tNormal: " << vertices[i].Normal.x << " " << vertices[i].Normal.y << " " << vertices[i].Normal.z << std::endl;
    }

    indices = {
        4, 3, 2,
        4, 2, 1,

        1, 2, 6,
        1, 6, 5,

        7, 6, 2,
        7, 2, 3,

        4, 8, 7,
        4, 7, 3,

        5, 8, 4,
        5, 4, 1,

        5, 6, 7,
        5, 7, 8,

    };

    for (unsigned int i = 0; i < indices.size(); i++) {
        indices[i] -= 1;
    }

    return Mesh(vertices, indices);
}

// reads the vertices and indices from the vectors and sets up the VAO, VBO, and EBO
void Mesh::setupMesh() {
    // Generate all our guys
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO, which organizes our other two buffers.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Write the vertices to the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Now bind and write our EBO. (Why is this done now? Don't know.)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set up the vertex attributes
    // -----------------------------
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // Color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    
    // Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); // this offsetof stuff is crazy cool and useful
    // -----------------------------
    glBindVertexArray(0); // cleannnup!
}