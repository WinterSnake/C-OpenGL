#version 450 core
in vec4 fragColor;
in vec2 fragTextureCoords;

out vec4 color;

uniform sampler2D textureSample;

void main()
{
	color = texture(textureSample, fragTextureCoords) * fragColor;
}
