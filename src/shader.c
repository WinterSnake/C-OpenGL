/*
	OpenGL
	- Shader

	Written By: Ryan Smith
*/

#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

#include "shader.h"

static GLuint ShaderCompile(GLenum type, const char* source)
{
	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);
	GLint result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shaderId, length, &length, message);
		message[length + 1] = 0;
		fprintf(stderr, "Unable to compile shader: '%s'.\n", message);
		return 0;
	}
	return shaderId;
}

static char* ShaderReadFromFile(const char* filePath)
{
	FILE* fp = fopen(filePath, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Unable to open file '%s'.\n", filePath);
		return NULL;
	}
	fseek(fp, 0L, SEEK_END);
	size_t length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* contents = (char*)malloc(length * sizeof(char) + 1);
	if (contents == NULL)
	{
		fprintf(stderr, "Unable to allocate enough space to read shader.\n");
		fclose(fp);
		return NULL;
	}
	fread(contents, sizeof(char), length, fp);
	fclose(fp);
	contents[length] = 0;
	return contents;
}

Shader ShaderCreate(const char* vertSource, const char* fragSource)
{
	// TODO: Handle errors
	GLuint vertId = ShaderCompile(GL_VERTEX_SHADER,   vertSource);
	GLuint fragId = ShaderCompile(GL_FRAGMENT_SHADER, fragSource);
	// Create program
	GLuint prgmId = glCreateProgram();
	glAttachShader(prgmId, vertId);
	glAttachShader(prgmId, fragId);
	glLinkProgram(prgmId);
	glValidateProgram(prgmId);
	// Cleanup shaders
	glDeleteShader(vertId);
	glDeleteShader(fragId);
	// Construct and return shader object
	return (struct Shader) { .Id = prgmId };
}

struct Shader ShaderCreateFromFile(const char* vertFile, const char* fragFile)
{
	char* vertSource = ShaderReadFromFile(vertFile);
	if (vertSource == NULL)
		return (struct Shader) { .Id = 0 };
	char* fragSource = ShaderReadFromFile(fragFile);
	if (fragSource == NULL)
	{
		free(vertSource);
		return (struct Shader) { .Id = 0 };
	}
	struct Shader shader = ShaderCreate(vertSource, fragSource);
	free(vertSource);
	free(fragSource);
	return shader;
}

void ShaderStart(struct Shader shader)
{
	glUseProgram(shader.Id);
}

void ShaderDelete(struct Shader shader)
{
	glDeleteProgram(shader.Id);
}
