#version 330 core

in vec2 out_uv;

out vec4 fragmentColor;

uniform sampler2D imageTexture;

void main() 
{
	vec2 flippedCoords = vec2(out_uv.x, 1.0f - out_uv.y);
	fragmentColor = texture(imageTexture, flippedCoords).rgba;
}