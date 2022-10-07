#include <gl/glew.h>
#include <iostream>
#include "Window.h"


std::unique_ptr<Window> createWindow()
{
	//Initialise GLFW
	if (!glfwInit()) {
		std::cout << "Could not initialise GLFW" << std::endl;
		return nullptr;
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
		return nullptr;
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
		return nullptr;
	}
	
	Window window{ (GLfloat)bufferW, (GLfloat)bufferH, mainWindow };
	glViewport(0, 0, window.bufferW, window.bufferH);

	return std::make_unique<Window>(std::move(window));
}
