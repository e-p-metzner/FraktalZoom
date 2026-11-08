#include <iostream>
#include <GL/glew.h>
#include "GLErrorHandler.h"

void GLClearError() {

	while(glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line) {
	bool error_free = true;

	while(GLenum error = glGetError()) {
		std::cerr << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
		error_free = false;
	}

	return error_free;
}

