#include "Mesh.h"


Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices) : m_vertices{vertices}, 
m_indices{indices}
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        {
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Legit to unbing here as there is more than one EBO
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // There is only one EBO so it should be unbound after the VAO has been unbound   
}

void Mesh::draw() const{
    glBindVertexArray(m_VAO);
			{
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			}
	glBindVertexArray(0);
}