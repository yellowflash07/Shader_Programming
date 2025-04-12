#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#define CHECK_GL_ERROR() { \
	GLenum err; \
	while ((err = glGetError()) != GL_NO_ERROR) { \
		printf("OpenGL error: %d\n", err); \
	} \
}