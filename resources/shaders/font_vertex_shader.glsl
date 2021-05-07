#version 330 core

in vec4 vertex;
out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 rotation;

void main() {
	gl_Position = rotation * projection * vec4(vertex.xy, 0.0, 1.0);
	TexCoords = vertex.zw;
}