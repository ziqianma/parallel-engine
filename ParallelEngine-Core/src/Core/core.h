#pragma once

#include "common.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Core {
	class SceneNode {

	};

	class Renderer {
	public:
		void render(SceneNode* scene);
	private:
	};

	class Application {
	public:
		Application(int screenWidth, int screenHeight) : m_scrWidth(screenWidth), m_scrHeight(screenHeight) {}
		void init(Renderer& renderer);
	private:
		int m_scrWidth, m_scrHeight;
		void handleWindowInput(GLFWwindow* window);
	};
}