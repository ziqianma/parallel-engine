#include "core.h"

namespace Core {

    void Renderer::render(SceneNode* scene) {
        scene->render();
        for (int i = 0; i < scene->getChildren().size(); i++) {
            render(scene->getChildren()[i]);
        }
    }

    Renderer::~Renderer() {
        delete m_sceneRoot;
    }

    SceneNode::~SceneNode() {
        parent = NULL;
        for (int i = 0; i < children.size(); i++) {
            // recursively delete children
            delete children[i];
        }
    }

    void SceneNode::addChild(SceneNode* node) {
        node->parent = this;
        children.push_back(node);
    }

	void Application::init(Renderer& renderer, SceneNode* scene) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Construct the window
        GLFWwindow* window = glfwCreateWindow(m_scrWidth, m_scrHeight, "Parallel Engine", nullptr, nullptr);
        if (!window)
        {
            std::cout << "Failed to create the GLFW window\n";
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW\n";
            glfwTerminate();
        }

        // Handle view port dimensions
        glViewport(0, 0, m_scrWidth, m_scrHeight);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

        // This is the render loop
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            handleWindowInput(window);
            renderer.render(scene);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
	}

    void Application::handleWindowInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}