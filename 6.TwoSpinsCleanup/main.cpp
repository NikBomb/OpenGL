#include <gl/glew.h>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Mesh.h"
#include "Window.h"
#include "Shaders.h"

GLuint u_model, u_projection;

std::vector<Mesh> createTriangles() {
	
	std::vector<unsigned int> indices = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};


	std::vector<GLfloat> vertices = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	return std::vector<Mesh>{Mesh(vertices, indices), Mesh(vertices, indices)};
}

int main()
{

	auto mainWindow = createWindow();
	auto meshes = createTriangles();

	glm::mat4 projection = glm::perspective(45.0f, mainWindow->bufferW / mainWindow->bufferH, 0.1f, 100.0f);
	Shaders shaders{"../../../../6.TwoSpinsCleanup/vertexShader.s", "../../../../6.TwoSpinsCleanup/fragShader.s"};
	std::vector<std::pair<GLuint*, std::string>> uniforms{ std::make_pair(&u_model, "model"), 
														   std::make_pair(&u_projection, "projection") };
	shaders.compileShaders(uniforms);

	glEnable(GL_DEPTH_TEST);
    meshes[0].model = glm::translate(meshes[0].model, glm::vec3(0.0, -0.5f, -2.5f));
	meshes[0].model = glm::scale(meshes[0].model, glm::vec3(0.4f, 0.4f, 1.0f));
    meshes[1].model = glm::translate(meshes[1].model, glm::vec3(0.0, 1.0f, -2.5f));
    meshes[1].model = glm::scale(meshes[1].model, glm::vec3(0.4f, 0.4f, 1.0f));
	while (!glfwWindowShouldClose(mainWindow->window)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaders.getShaderProgram());
		{
			for (auto& mesh : meshes) {
				mesh.model = glm::rotate(mesh.model, glm::radians(0.01f), glm::vec3(0.f, 1.f, 0.f));
				glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(mesh.model));
				glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
				mesh.draw();
			}

		}
		glUseProgram(0);
		glfwSwapBuffers(mainWindow->window);
	}

	return 0;
}
