#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/mat4x4.hpp>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GLuint VAO, VBO, shader, u_model;


static const GLchar* vertexShader = "                    \n\
#version 330                                             \n\
layout (location = 0) in vec3 pos;                       \n\
uniform mat4 model;                                      \n\
out vec4 vcolor;                                         \n\
                                                         \n\
void main()                                              \n\
{                                                        \n\
	gl_Position = model * vec4(pos, 1.0);                \n\
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


void createTriangle() {

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
    glBindVertexArray(0);


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

	glm::mat4 model(1.0f);
	//model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
	
	glViewport(0, 0, bufferW, bufferH);
	createTriangle();
	compileShaders();

	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		{
			glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			{
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			glBindVertexArray(0);
		}
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
