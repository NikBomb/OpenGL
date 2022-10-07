#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <memory>

struct Window{
	GLfloat bufferW;
	GLfloat bufferH;
	GLFWwindow* window;
};


std::unique_ptr<Window> createWindow();

#endif // !WINDOW_H
