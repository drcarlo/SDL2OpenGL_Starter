#version 330 core

in vec2 out_uv;

uniform sampler2D textureSampler;

out vec4 fragmentColor;

void main() 
{

	fragmentColor = texture(textureSampler, out_uv).rgba;
}