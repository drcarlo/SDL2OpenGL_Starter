#pragma once
#include <GL/glew.h>

struct Vertex {
	Vertex(float _x, float _y, float _z, float _u, float _v) {
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}
	float x, y, z, u, v;
};

class Model {
public:
	virtual GLuint getVbo() = 0;
	virtual GLuint getIbo() = 0;
	virtual GLuint getIndexCount() = 0;
};