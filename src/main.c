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

const char* vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	// GLFW: Create Window
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

	printf("%s\n", glGetString(GL_VERSION));

	// OpenGL: Shader
	struct Shader triangleShader = CreateShader(vertexShaderSource, fragmentShaderSource);
	printf("Created new shader with Id: %u\n", triangleShader.Id);


	// OpenGL: Buffers
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float clearColorArray[4];
	struct Color clearColor = { .R = 0x17, .G = 0x26, .B = 0x4A, .A = 0xFF };
	NormalizeColor(clearColor, clearColorArray);
	printf("%f, %f, %f, %f\n", clearColorArray[0], clearColorArray[1], clearColorArray[2], clearColorArray[3]);

	// GLFW: Loop
	while (!glfwWindowShouldClose(window))
	{
		/* Rendering */
		// Clear
		glClearColor(clearColorArray[0], clearColorArray[1], clearColorArray[2], clearColorArray[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		// Triangle
		StartShader(triangleShader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap Buffer
		glfwSwapBuffers(window);
		/* Events */
		glfwPollEvents();
		int escapeKeyState = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (escapeKeyState == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// OpenGL: Cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	DeleteShader(triangleShader);

	// GLFW: Close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
