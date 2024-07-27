/*
	OpenGL Context Experiments
	- Loader Generated from GLAD: https://glad.dav1d.de/

	Written By: Ryan Smith
*/
#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	// GLFW: Initialize
	if (!glfwInit())
	{
		fprintf(stderr, "Unable to init GLFW.\n");
		return 1;
	}

	// GLFW: Create Window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Unable to create a GLFW window.\n");
		glfwTerminate();
		return 1;
	}

	// GLFW: OpenGL
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// GLFW: Loop
	while (!glfwWindowShouldClose(window))
	{
		/* Events */
		glfwPollEvents();
		int escapeKeyState = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (escapeKeyState == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		/* Rendering */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	// GLFW: Close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
