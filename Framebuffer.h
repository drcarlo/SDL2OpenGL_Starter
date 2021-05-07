#pragma once

#include <GL/glew.h>
#include "Utils.h"

namespace GE {
	class FrameBuffer {
	public:
		FrameBuffer(int _width, int _height) : width(_width), height(_height) {}
		~FrameBuffer();

		int init();
		unsigned int getTextureLocation() { return textureLocation; }
		void bind() { glBindFramebuffer(GL_FRAMEBUFFER, location); }
		void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, NULL); }


	private:
		unsigned int location = 0, textureLocation = 0, depthRenderBuffer = 0;
		unsigned int VAO, IBO, VBO;
		int width, height;
	};
}