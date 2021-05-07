#version 330 core

layout(location = 0) in vec4 vertexPosition; 
layout(location = 1) in vec2 uv;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 out_uv;


void main() 
{ 
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPosition;
	out_uv = uv;
}