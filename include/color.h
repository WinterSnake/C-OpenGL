/*
	OpenGL
	- Color

	Written By: Ryan Smith
*/
#pragma once
#ifndef OPENGL_COLOR_H
#define OPENGL_COLOR_H

#include <stdint.h>

typedef struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
} Color;

void NormalizeColor(struct Color, float* floatBuffer);

#endif
