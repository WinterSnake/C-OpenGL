/*
	OpenGL Context Experiments
	- Loader Generated from GLAD: https://glad.dav1d.de/

	Written By: Ryan Smith
*/
#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

	// Image
	int width, height, channels;
	const char* file = "./assets/wall.jpg";
	uint8_t* data = stbi_load(file, &width, &height, &channels, 0);
	if (data == NULL)
	{
		fprintf(stderr, "Failed to load image from '%s'.\n", file);
		return 1;
	}
	printf("Image loaded: (%i, %i)[Channels: %i] Valid == %s\n", width, height, channels, data != NULL ? "true" : "false");

	glViewport(0, 0, WIDTH, HEIGHT);


	// OpenGL: Shader
	struct Shader rectShader = ShaderCreateFromFile("./shaders/basic.vert", "./shaders/basic.frag");
	printf("Created new shader with Id: %u\n", rectShader.Id);

	// OpenGL: Buffers
	GLfloat vertices[] = {
		// Position(vec4)       ||Color(vec4)           ||Texture Coord(vec2)
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	};
	GLuint indicies[] = {
		0, 1, 3,
		1, 2, 3,
	};

	GLuint vao, vbo, ebo, texture;
	/// Vertex [VAO]
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	/// Verticies [VBO]
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (4 + 4 + 2) * 4 * sizeof(float), vertices, GL_STATIC_DRAW);
	// [Position]
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// [Color]
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// [Texture Coord]
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(2);
	/// Indexes [EBO]
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indicies, GL_STATIC_DRAW);
	/// Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// OpenGL: Color
	float clearColorArray[4];
	struct Color clearColor = { .R = 0x17, .G = 0x26, .B = 0x4A, .A = 0xFF };
	NormalizeColor(clearColor, clearColorArray);

	// GLFW: Loop
	while (!glfwWindowShouldClose(window))
	{
		/* Rendering */
		// Clear
		glClearColor(clearColorArray[0], clearColorArray[1], clearColorArray[2], clearColorArray[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		// Color + Draw Rect
		ShaderStart(rectShader);
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
