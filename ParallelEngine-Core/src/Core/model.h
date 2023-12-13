#pragma once

#include "mesh.h"
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	std::string path;
	Model(std::string path) : path(path) {
		loadModel(path);
	}
	void Draw(Shader& shader);
	void setupTextures(Shader& shader);
private:
	const glm::vec3* offsets;
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texType);
};