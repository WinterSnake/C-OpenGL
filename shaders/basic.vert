#version 450 core
in vec4 position;
in vec4 vertColor;
in vec2 vertTextureCoords;

out vec4 fragColor;
out vec2 fragTextureCoords;

uniform mat4 transform;

void main()
{
	gl_Position = transform * position;
	fragColor = vertColor;
	fragTextureCoords = vertTextureCoords;
}
