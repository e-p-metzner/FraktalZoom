#ifndef CAPPLET_CSHAPE_HPP_
#define CAPPLET_CSHAPE_HPP_

#include <vector>
#include <GL/glew.h>

namespace CApplet {

class CShape {
private:
	GLuint vao;
	std::vector<GLuint> vbos;
	std::vector<GLuint> attribs;
protected:
public:
	GLuint ibo;
	int indecescount;
	CShape();
	virtual ~CShape();
	void bind();
	void unbind(bool only_vao);
	void storeIndeces(int count, unsigned int* data);
	void storeInts(int attrib, int dim, int count, int* data);
	void storeFloats(int attrib, int dim, int count, float* data);
};

}

#endif /* CAPPLET_CSHAPE_HPP_ */
