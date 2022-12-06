#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

using namespace std;

#define MAX_BONE_INFLUENCE 4

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, std::vector<lm::vec3> colors);

    void Draw(Shader& shader, lm::mat4& modelMatrix, lm::vec3& camPos, lm::mat4* VPMatrix = nullptr);

private:
    // render data 
    unsigned int VBO, EBO, VAO;

    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    std::vector<lm::vec3> colors;

    // initializes all the buffer objects/arrays
    void setupMesh();
};