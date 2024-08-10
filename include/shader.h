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

struct Shader ShaderCreate(const char*, const char*);
struct Shader ShaderCreateFromFile(const char*, const char*);
void ShaderStart(struct Shader);
void ShaderDelete(struct Shader);

#endif
