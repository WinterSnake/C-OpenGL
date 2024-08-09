/*
	OpenGL
	- Shader

	Written By: Ryan Smith
*/

#include "glad/glad.h"

#include "shader.h"

static GLuint CompileOpenGLShader(GLenum type, const char* source)
{
	// TODO: Handle errors
	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);
	return shaderId;
}

Shader CreateShader(const char* vertexSource, const char* fragmentSource)
{
	// TODO: Handle errors
	GLuint shaderId   = glCreateProgram();
	GLuint vertexId   = CompileOpenGLShader(GL_VERTEX_SHADER,   vertexSource);
	GLuint fragmentId = CompileOpenGLShader(GL_FRAGMENT_SHADER, fragmentSource);
	// Create program
	glAttachShader(shaderId, vertexId);
	glAttachShader(shaderId, fragmentId);
	glLinkProgram(shaderId);
	glValidateProgram(shaderId);
	// Cleanup shaders
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
	// Construct and return shader object
	return (struct Shader){
		.Id = shaderId
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
