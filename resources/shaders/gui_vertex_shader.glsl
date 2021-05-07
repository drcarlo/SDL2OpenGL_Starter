#version 330 core

in vec3 vertexPosition; 
in vec2 vertexUVs;

uniform mat4 projectionMatrix;

out vec2 out_uv;

void main() 
{ 
	gl_Position = projectionMatrix * vec4(vertexPosition.xy, 0.0f, 1.0f);
	out_uv = vertexUVs;
}