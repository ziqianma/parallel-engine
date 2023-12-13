#include "model.h"
namespace Core {
	void Model::Draw(Shader& shader) {
		for (Mesh m : meshes) {
			m.Draw(shader);
		}
	}

	void Model::loadModel(std::string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of("/"));
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {

		// node->mMeshes contain indicies of meshes inside scene->mMeshes
		// scene->mMeshes contains meshes which make up the entire model.
		// We loop through all references to meshes within the node (indices of meshes inside the scene)
		// Then translate those aiMesh* to our native Mesh type (using processMesh) and add to our mesh list.
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		// Now we recursively process all children of the current node, making sure to add all meshes of the children to our list
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;

		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// Translate all vertex data
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

			Vertex v;
			glm::vec3 temp;
			temp.x = mesh->mVertices[i].x;
			temp.y = mesh->mVertices[i].y;
			temp.z = mesh->mVertices[i].z;
			v.position = temp;

			temp.x = mesh->mNormals[i].x;
			temp.y = mesh->mNormals[i].y;
			temp.z = mesh->mNormals[i].z;
			v.normal = temp;


			glm::vec2 texCoord = glm::vec2(0.0f, 0.0f);
			if (mesh->mTextureCoords[0]) {
				texCoord.x = mesh->mTextureCoords[0][i].x;
				texCoord.y = mesh->mTextureCoords[0][i].y;
			}

			v.texCoord = texCoord;
			vertices.push_back(v);

		}

		// Translate index data
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		aiColor3D ambient(0.f, 0.f, 0.f);
		aiColor3D diffuse(0.f, 0.f, 0.f);
		aiColor3D specular(0.f, 0.f, 0.f);

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			loadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, TextureType::DIFFUSE);
			loadMaterialTextures(material, aiTextureType::aiTextureType_SPECULAR, TextureType::SPECULAR);
			loadMaterialTextures(material, aiTextureType::aiTextureType_NORMALS, TextureType::BUMP);

			material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		}

		std::vector<unsigned int> textureIDs;
		for (Texture t : textures) {
			textureIDs.push_back(t.id);
		}

		return Mesh(vertices, indices, textureIDs, glm::vec3(ambient.r, ambient.g, ambient.b), glm::vec3(diffuse.r, diffuse.g, diffuse.b), glm::vec3(specular.r, specular.g, specular.b));
	}

	void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texType) {
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString path;
			mat->GetTexture(type, i, &path);

			// load the current texture from the materials list
			Texture currTexture = TextureLoader::loadTexture(path.C_Str(), directory, texType);

			// add loaded texture ID (name) to model tex id list
			textures.push_back(currTexture);
		}
	}

	void Model::setupTextures(Shader& shader) {

		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int bumpNr = 1;

		std::string textureName;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			glBindTexture(GL_TEXTURE_2D, textures[i].id);

			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			TextureType name = textures[i].type;
			switch (name) {
			case TextureType::DIFFUSE:
				textureName = "diffuse";
				number = std::to_string(diffuseNr++);
				break;
			case TextureType::SPECULAR:
				textureName = "specular";
				number = std::to_string(specularNr++);
				break;
			case TextureType::BUMP:
				textureName = "bump";
				number = std::to_string(bumpNr++);
				break;
			default:
				break;
			}

			shader.bind();
			// bind textures to uniforms
			shader.addUniform1i(("material." + textureName + number).c_str(), i);
			shader.unbind();
		}
	}
}