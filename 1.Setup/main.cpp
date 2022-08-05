#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


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

	auto mainWindow = glfwCreateWindow(800, 600, "TEST", NULL, NULL);
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

	glViewport(0, 0, bufferW, bufferH);
	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();
		glEnable(GL_SCISSOR_TEST);  // Draw Single Pixel
		glScissor(100, 200, 1, 1);
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		// Remember to disable scissor test, or, perhaps reset the scissor rectangle:
		glDisable(GL_SCISSOR_TEST);
		glfwSwapBuffers(mainWindow);
	}

	return 0;





	return 0;
}
