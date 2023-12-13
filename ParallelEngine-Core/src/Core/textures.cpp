#include "textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<const std::string, Texture> TextureLoader::loadedTextures;

/**
 * loadTexture - returns texture data, from the result of loading in a texture inside the OpenGL context
 *	path - relative texture path
 *  directory - texture directory (absolute)
 *  type - TextureType enum (to correctly assign to materials)
 */
Texture TextureLoader::loadTexture(const char* path, const std::string& directory, TextureType type) {
	for (const auto& [texPath, texture] : loadedTextures) {
		if (directory + path == texPath) {
			return texture;
		}
	}

	Texture texture = TextureFromFile(path, directory, type, false);
	std::string textureKey = std::string(directory + path);
	loadedTextures[textureKey] = texture;

	return texture;
}

Texture TextureLoader::TextureFromFile(const char* path, const std::string& directory, TextureType type, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	Texture result;
	result.id = textureID;
	result.path = path;
	result.type = type;

	return result;
}