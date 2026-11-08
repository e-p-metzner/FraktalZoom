#include "GLErrorHandler.h"
#include "CShape.h"

namespace CApplet {

CShape::CShape() {
	GLCall(glGenVertexArrays(1, &vao))
	ibo = 0;
	indecescount = 0;
}

CShape::~CShape() {
	glBindVertexArray(vao);
	for(GLuint vbo: vbos) {
		glDeleteBuffers(1, &vbo);
	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
}

void CShape::storeIndeces(int count, unsigned int* data) {
	glBindVertexArray(vao);
	glGenBuffers(1, &ibo);
	vbos.push_back(ibo);
	indecescount = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo))
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
	glBindVertexArray(0);
}

void CShape::storeInts(int attrib, int dim, int count, int* data) {
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo))
	GLCall(glBufferData(GL_ARRAY_BUFFER, dim * count * sizeof(int), data, GL_STATIC_DRAW))
	GLCall(glEnableVertexAttribArray(attrib))
	GLCall(glVertexAttribPointer(attrib, dim, GL_INT, GL_FALSE, 0, 0))
	attribs.push_back(attrib);
	glBindVertexArray(0);
}

void CShape::storeFloats(int attrib, int dim, int count, float* data) {
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo))
	GLCall(glBufferData(GL_ARRAY_BUFFER, dim * count * sizeof(float), data, GL_STATIC_DRAW))
	GLCall(glEnableVertexAttribArray(attrib))
	GLCall(glVertexAttribPointer(attrib, dim, GL_FLOAT, GL_FALSE, 0, 0))
	attribs.push_back(attrib);
	glBindVertexArray(0);
}

void CShape::bind() {

	GLCall(glBindVertexArray(vao))
	for(GLuint attrib: attribs) {
		GLCall(glEnableVertexAttribArray(attrib))
	}
}

void CShape::unbind(bool only_vao) {
	if(!only_vao) {
		for(GLuint attrib : attribs) {
			glDisableVertexAttribArray(attrib);
		}
	}
	glBindVertexArray(0);
}

}

