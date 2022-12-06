#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "IResource.h"
#include "Mesh.h"
#include "ResourcesManager.h"

class Model : public IResource
{
public:

    // constructor, expects a filepath to a 3D model.
    Model(std::string path, Texture* texture, Camera* cam, bool gamma = false);

    static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(lm::mat4& modelMatrix, Shader& shader);
	void Draw(lm::mat4& modelMatrix, Shader& shader, bool usingDifferentShader);

	lm::mat4& GetVPMatrix();

private:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    bool gammaCorrection;
    std::string path;
    Texture* texture = nullptr;

    void loadModel();

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};