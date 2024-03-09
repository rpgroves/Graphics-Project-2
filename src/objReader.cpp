#include "mesh.h"
#include <regex>

void addFaceToIndices(std::vector<unsigned int> face, std::vector<unsigned int> &indices);

Mesh loadObjFile(const char* filename) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return Mesh(vertices, indices);
    }

    //std::regex pattern("((\d*)\/(\d*)\/(\d*)\s?)*");
    std::regex pattern("/(\\d+)(?:\\/(\\d+)?\\/(\\d+))?"); // This is the pattern for a single vertex in a face
    // Group 1 is position, group 2 is texture, group 3 is normal

    for (std::string line; getline(file, line);) { 
        std::string lineTemp = line;  
        // Reading vertex (position)
        if(line != "" && line.at(0) == 'v' && line.at(1) == ' ') {
            Vertex vertex;
            lineTemp = lineTemp.substr(2);
            sscanf(lineTemp.c_str(), "%f %f %f", &vertex.Position.x, &vertex.Position.y, &vertex.Position.z); // huh
            vertices.push_back(vertex);
        
        } 

        // Reading faces (indices)
        else if(line != "" && line.at(0) == 'f' && line.at(1) == ' ') {
            std::vector<unsigned int> face;
            lineTemp = lineTemp.substr(2);
            // Get all matches of the pattern
            std::smatch match;
            while (regex_search(lineTemp, match, pattern)) {
                if (match[0].matched) {
                    face.push_back(std::stoi(match[1].str()));
                }
            }
            addFaceToIndices(face, indices);
        }
    }
    // for (unsigned int i = 0; i < vertices.size(); i++) {
    //     std::cout << "Vertex " << i << std::endl;
    //     std::cout << "\tPosition: " << vertices[i].Position.x << " " << vertices[i].Position.y << " " << vertices[i].Position.z << std::endl;
    //     std::cout << "\tColor: " << vertices[i].Color.x << " " << vertices[i].Color.y << " " << vertices[i].Color.z << std::endl;
    //     std::cout << "\tNormal: " << vertices[i].Normal.x << " " << vertices[i].Normal.y << " " << vertices[i].Normal.z << std::endl;
    // }

    return Mesh(vertices, indices);
}

void addFaceToIndices(std::vector<unsigned int> face, std::vector<unsigned int> &indices) {
    // If the face has 3 vertices:
    if (face.size() == 3) {
        indices.push_back(face[0]);
        indices.push_back(face[1]);
        indices.push_back(face[2]);
    }

    else if (face.size() == 4) {
        indices.push_back(face[0]);
        indices.push_back(face[1]);
        indices.push_back(face[2]);
        indices.push_back(face[0]);
        indices.push_back(face[2]);
        indices.push_back(face[3]);
    }

    else std::cout << "Face has " << face.size() << " vertices, not supported." << std::endl;
}
