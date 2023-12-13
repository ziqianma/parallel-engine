#include "shader.h"

namespace Core {
    void BaseShader::addUniform4f(const std::string& name, float x, float y, float z, float w) const {
        glUseProgram(_shaderProgram);
        glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
        glUseProgram(0);
    }

    void BaseShader::addUniform3f(const std::string& name, float x, float y, float z) const {
        glUseProgram(_shaderProgram);
        glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
        glUseProgram(0);
    }

    void BaseShader::addUniform1i(const std::string& name, int x) const {
        glUseProgram(_shaderProgram);
        glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), x);
        glUseProgram(0);
    }

    void BaseShader::addUniform1f(const std::string& name, float x) const {
        glUseProgram(_shaderProgram);
        glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), x);
        glUseProgram(0);
    }

    void BaseShader::addUniformMat4(const std::string& name, glm::mat4 data) {
        glUseProgram(_shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
        glUseProgram(0);
    }

    void BaseShader::addUniformMat3(const std::string& name, glm::mat3 data) {
        glUseProgram(_shaderProgram);
        glUniformMatrix3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
        glUseProgram(0);
    }

    void BaseShader::bind() {
        glUseProgram(_shaderProgram);
    }

    void BaseShader::unbind() {
        glUseProgram(0);
    }

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            _vertexShaderSourceCode = vShaderStream.str();
            _fragmentShaderSourceCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
    }

    void Shader::createShaderProgram() {
        int success;
        char infoLog[512];

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vsrc = _vertexShaderSourceCode.c_str();
        glShaderSource(vertexShader, 1, &vsrc, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fsrc = _fragmentShaderSourceCode.c_str();
        glShaderSource(fragmentShader, 1, &fsrc, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        _shaderProgram = shaderProgram;
    }

    ComputeShader::ComputeShader(const char* computeShaderPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::ifstream cShaderFile;
        // ensure ifstream objects can throw exceptions:
        cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            cShaderFile.open(computeShaderPath);
            std::stringstream cShaderStream;
            // read file's buffer contents into streams
            cShaderStream << cShaderFile.rdbuf();
            // close file handlers
            cShaderFile.close();
            // convert stream into string
            _computeShaderSourceCode = cShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::COMPUTE_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
    }

    void ComputeShader::createShaderProgram() {
        int success;
        char infoLog[512];

        unsigned int computeShader;
        computeShader = glCreateShader(GL_COMPUTE_SHADER);
        const char* csrc = _computeShaderSourceCode.c_str();
        glShaderSource(computeShader, 1, &csrc, NULL);
        glCompileShader(computeShader);
        glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, computeShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::COMPUTE_SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(computeShader);

        _shaderProgram = shaderProgram;
    }
}