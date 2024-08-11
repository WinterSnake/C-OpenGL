#version 450 core
in vec4 fragColor;
in vec2 fragTextureCoords;

uniform sampler2D textureSample;

out vec4 color;

void main()
{
	color = texture(textureSample, fragTextureCoords) * fragColor;
}
