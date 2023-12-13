#include "mesh.h"

namespace Core {
	// Constrctor intializes mesh data along with VAO, VBO and EBO
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& textureIDs, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
		this->vertices = vertices;
		this->indices = indices;
		this->textureIDs = textureIDs;

		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		setupMesh();
	}

	void Mesh::setupMesh() {
		// Generate VAO and VBO/EBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind vertex attributes to VAO
		glBindVertexArray(VAO);

		// Bind VBO/EBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// First attrib, position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // stride is the size of each VERTEX, attribs are determined through size and offset.

		// Second attrib, normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); //offsetof(S, M) gets the byte offset of variable M in struct S

		// Third attrib, texture coordinate
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void Mesh::Draw(Shader& shader) {

		shader.bind();
		shader.addUniform3f("material.ambient", ambient.r, ambient.g, ambient.b);
		shader.addUniform3f("material.diffuse", diffuse.r, diffuse.g, diffuse.b);
		shader.addUniform3f("material.specular", specular.r, specular.g, specular.b);

		for (int i = 0; i < textureIDs.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		}

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader.unbind();
	}
}