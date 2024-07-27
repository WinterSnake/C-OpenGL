/*
	OpenGL Context Experiments

	Written By: Ryan Smith
*/
#include <stdio.h>
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Unable to create a GLFW window.\n");
		glfwTerminate();
		return 1;
	}

	// GLFW: Loop
	while (!glfwWindowShouldClose(window))
	{
		/* Events */
		glfwPollEvents();
		int escapeKeyState = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (escapeKeyState == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		/* Rendering */
		glfwSwapBuffers(window);
	}

	// GLFW: Close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
