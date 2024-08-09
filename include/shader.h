/*
	OpenGL
	- Shader

	Written By: Ryan Smith
*/
#pragma once
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <stdint.h>

typedef struct Shader
{
	unsigned int Id;
} Shader;

struct Shader CreateShader(const char*, const char*);
struct Shader CreateShaderFromFile(const char*, const char*);
void StartShader(struct Shader);
void DeleteShader(struct Shader);

#endif
