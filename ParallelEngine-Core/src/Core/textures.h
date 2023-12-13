#pragma once
#include "common.h"

namespace Core {
	enum TextureType {
		DIFFUSE,
		SPECULAR,
		BUMP
	};

	struct Texture {
		unsigned int id;
		TextureType type;
		const char* path;
	};

	class TextureLoader {
	public:
		static Texture loadTexture(const char* path, const std::string& directory, TextureType type);
	private:
		static std::map<const std::string, Texture> loadedTextures;
		static Texture TextureFromFile(const char* path, const std::string& directory, TextureType type, bool gamma);
	};
}