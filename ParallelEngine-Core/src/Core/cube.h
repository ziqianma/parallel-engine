#pragma once
#include "common.h"
#include "shader.h"
#include "mesh.h"
#include "textures.h"
#include "entity.h"

namespace Core {
    class Cube : Entity {
    public:
        Cube() {
            vertices = new float[180]{
                // Back face
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
                // Front face
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
                // Left face
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
                // Right face
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
                // Bottom face          
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
                // Top face
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
            };

            setupCubeMesh();
        }
        Cube(std::string& texturePath);
        void Draw(Shader& shader) override;
    private:
        Texture cubeTexture;
        unsigned int textureID;
        bool hasTexture = false;
        void setupCubeMesh();
    };
}