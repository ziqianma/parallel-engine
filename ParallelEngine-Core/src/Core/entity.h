#pragma once
#include "shader.h"

namespace Core {
	class Entity {
	public:
		~Entity() {
			delete[] vertices;
			delete[] indices;
		}
		virtual void Draw(Shader& shader) = 0;
	protected:
		unsigned int VAO, VBO;
		float* vertices;
		float* indices;
	};
}