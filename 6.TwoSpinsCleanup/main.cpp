#include <gl/glew.h>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Mesh.h"

GLuint VAO, VBO, EBO, shader, u_model, u_projection;


static const GLchar* vertexShader = "                    \n\
#version 330                                             \n\
layout (location = 0) in vec3 pos;                       \n\
uniform mat4 model;                                      \n\
uniform mat4 projection;								 \n\
out vec4 vcolor;                                         \n\
                                                         \n\
void main()                                              \n\
{                                                        \n\
	gl_Position = projection * model * vec4(pos, 1.0);   \n\
    vcolor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);         \n\
}";


static const GLchar* fragmentShader = "      \n\
#version 330                                 \n\
                                             \n\
out vec4 colour;                             \n\
in  vec4 vcolor;                             \n\
                                             \n\
void main()                                  \n\
{                                            \n\
    colour = vcolor;                         \n\
}";


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

void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* code = shaderCode;
	const GLchar* const* pcode = &code;
	const GLint codeSize = strlen(shaderCode);

	glShaderSource(theShader, 1, &shaderCode, &codeSize);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
};

void compileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		printf("Failed to create shader\n");
		return;
	}

	addShader(shader, vertexShader, GL_VERTEX_SHADER);
	addShader(shader, fragmentShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	u_model = glGetUniformLocation(shader, "model");
	u_projection = glGetUniformLocation(shader, "projection");
}

int main()
{
	//Initialise GLFW
	if (!glfwInit()) {
		std::cout << "Could not initialise GLFW" << std::endl;
		return 1;
	}

	//Setup GLFW props 

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core Profile = No Backwards Comp.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forw, Comp
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//create window 

	auto mainWindow = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
	if (!mainWindow) {
		std::cout << "Could not initialise Window" << std::endl;
		glfwTerminate();
		return 1;
	}

	int bufferW, bufferH;

	glfwGetFramebufferSize(mainWindow, &bufferW, &bufferH);

	glfwMakeContextCurrent(mainWindow);

	/*Setup GLEW*/
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Could not Initialise GLEW" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	/*Call into OPENGL from GLEW*/

	
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferW / (GLfloat)bufferH, 0.1f, 100.0f);
	

	glViewport(0, 0, bufferW, bufferH);
	auto meshes = createTriangles();
	compileShaders();
	glEnable(GL_DEPTH_TEST);
	std::vector<glm::mat4> models{glm::mat4(1.0f), glm::mat4(1.0f)};
    models[0] = glm::translate(models[0], glm::vec3(0.0, -0.5f, -2.5f));
    models[0] = glm::scale(models[0], glm::vec3(0.4f, 0.4f, 1.0f));
    models[1] = glm::translate(models[1], glm::vec3(0.0, 1.0f, -2.5f));
    models[1] = glm::scale(models[1], glm::vec3(0.4f, 0.4f, 1.0f));
	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);
		{
			models[0] = glm::rotate(models[0], glm::radians(0.01f), glm::vec3(0.f, 1.f, 0.f));
			glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(models[0]));
			glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
			meshes[0].draw();

			models[1] = glm::rotate(models[1], glm::radians(0.01f), glm::vec3(0.f, 1.f, 0.f));
			glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(models[1]));
			meshes[1].draw();

		}
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
