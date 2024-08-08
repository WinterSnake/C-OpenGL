/*
	OpenGL
	- Shader

	Written By: Ryan Smith
*/

#include "glad/glad.h"

#include "shader.h"

Shader CreateShader(const char* vertexSource, const char* fragmentSource)
{
	// TODO: Handle errors
	// Generate vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	// Generate fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	// Create program and return Id
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Cleanup shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// Construct shader object
	return (struct Shader){
		.Id = shaderProgram
	};
}

void StartShader(struct Shader shader)
{
	glUseProgram(shader.Id);
}

void DeleteShader(struct Shader shader)
{
	glDeleteProgram(shader.Id);
}
