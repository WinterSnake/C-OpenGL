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

#include "opengl.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	printf("New size: (%i, %i)\n", width, height);
	glViewport(0, 0, width, height);
}

int main(int argc, const char** argv)
{
	(void)argc;
	(void)argv;

	// GLFW: Initialize
	if (!glfwInit())
	{
		fprintf(stderr, "Unable to init GLFW.\n");
		return 1;
	}

	// GLFW: Window Options
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	// GLFW: Create Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Unable to create a GLFW window.\n");
		glfwTerminate();
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// GLFW: OpenGL
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	printf("%s\n", glGetString(GL_VERSION));

	glViewport(0, 0, WIDTH, HEIGHT);

	GLfloat vertices[] = {
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f,  0.5f,
	};
	GLuint indicies[] = {
		0, 1, 3,
		1, 2, 3,
	};

	// OpenGL: Buffers
	GLuint vao, vbo, ibo;

	/// Vertex [VAO]
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	/// Verticies [VBO]
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	/// Indexes [IBO]
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indicies, GL_STATIC_DRAW);

	// OpenGL: Color
	float clearColorArray[4];
	struct Color clearColor = { .R = 0x17, .G = 0x26, .B = 0x4A, .A = 0xFF };
	NormalizeColor(clearColor, clearColorArray);
	float rectColorArray[4];
	struct Color rectColor  = { .R = 0x00, .G = 0x00, .B = 0x00, .A = 0xFF };

	// OpenGL: Shader
	struct Shader rectShader = ShaderCreateFromFile("./shaders/basic.vert", "./shaders/basic.frag");
	printf("Created new shader with Id: %u\n", rectShader.Id);
	ShaderStart(rectShader);

	GLint location = glGetUniformLocation(rectShader.Id, "uColor");

	// GLFW: Loop
	while (!glfwWindowShouldClose(window))
	{
		/* Rendering */
		// Clear
		glClearColor(clearColorArray[0], clearColorArray[1], clearColorArray[2], clearColorArray[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		// Color + Draw Rect
		rectColor.R -= 1;
		rectColor.G += 1;
		rectColor.B += 5;
		NormalizeColor(rectColor, rectColorArray);
		glUniform4f(location, rectColorArray[0], rectColorArray[1], rectColorArray[2], rectColorArray[3]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		// Swap Buffer
		glfwSwapBuffers(window);
		/* Events */
		glfwPollEvents();
		int escapeKeyState = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (escapeKeyState == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// OpenGL: Cleanup
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	ShaderDelete(rectShader);

	// GLFW: Close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
