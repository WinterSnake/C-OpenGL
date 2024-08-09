/*
	OpenGL
	- Color

	Written By: Ryan Smith
*/

#include "color.h"

void NormalizeColor(struct Color color, float* floatBuffer)
{
	floatBuffer[0] = (float)color.R / 255.0f;
	floatBuffer[1] = (float)color.G / 255.0f;
	floatBuffer[2] = (float)color.B / 255.0f;
	floatBuffer[3] = (float)color.A / 255.0f;
}
