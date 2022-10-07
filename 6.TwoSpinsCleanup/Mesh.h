#ifndef MESH_H
#define MESH_H



#include <vector>
#include <gl/glew.h>
#include <glm\mat4x4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Mesh {
    public:
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    glm::mat4 model{ 1.0f };
    void draw() const;
    private:

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    std::vector<unsigned int> m_indices;
    std::vector<GLfloat> m_vertices;

};

#endif