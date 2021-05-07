#version 330 core

in vec2 TexCoords;
uniform sampler2D text;
uniform vec3 textColour;

out vec4 colourOut;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	colourOut = vec4(textColour.xyz, 1.0) * sampled;
}