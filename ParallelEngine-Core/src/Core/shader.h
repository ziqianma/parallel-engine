#pragma once

#include "common.h"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

namespace Core {
    class BaseShader {
    public:
        void addUniform4f(const std::string& name, float x, float y, float z, float w) const;
        void addUniform3f(const std::string& name, float x, float y, float z) const;
        void addUniform1i(const std::string& name, int x) const;
        void addUniform1f(const std::string& name, float x) const;
        void addUniformMat4(const std::string& name, glm::mat4 data);
        void addUniformMat3(const std::string& name, glm::mat3 data);
        void bind();
        void unbind();
        virtual void createShaderProgram() = 0;
    protected:
        unsigned int _shaderProgram;
        std::vector<std::string> uniforms;
    };

    class ComputeShader : public BaseShader {
    public:
        ComputeShader(const char* computeShaderPath);
        void createShaderProgram();
    private:
        std::string _computeShaderSourceCode;

    };

    class Shader : public BaseShader {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        void createShaderProgram();
    private:
        std::string _vertexShaderSourceCode;
        std::string _fragmentShaderSourceCode;
    };
}