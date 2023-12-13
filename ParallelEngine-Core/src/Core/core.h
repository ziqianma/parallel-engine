#pragma once

#include "common.h"
#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Core {
	class SceneNode {
	public:
		SceneNode(Shader& shader) : parent(NULL), shader(shader) {}

		~SceneNode();
		void addChild(SceneNode* child);
		virtual void render() = 0;
		std::vector<SceneNode*> getChildren() { return children; }
	private:
		SceneNode* parent;
		Shader shader;
		std::vector<SceneNode*> children;
	};
	
	class Renderer {
	public:
		~Renderer();
		void render(SceneNode* scene);
	private:
		SceneNode* m_sceneRoot;
	};

	class Application {
	public:
		Application(int screenWidth, int screenHeight) : m_scrWidth(screenWidth), m_scrHeight(screenHeight) {}
		void init(Renderer& renderer, SceneNode* scene);
	private:
		int m_scrWidth, m_scrHeight;
		void handleWindowInput(GLFWwindow* window);
	};
}