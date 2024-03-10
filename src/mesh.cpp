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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); // this offsetof stuff is crazy cool and useful
    
    // Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    // -----------------------------
    glBindVertexArray(0); // cleannnup!
}