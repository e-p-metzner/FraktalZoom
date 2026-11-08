#ifndef CAPPLET_CSHADER_HPP_
#define CAPPLET_CSHADER_HPP_

#include <string>
#include <vector>
#include <GL/glew.h>

namespace CApplet {

class CShader {
private:
	std::string ownPth;
	std::string readFile(const std::string& filepath);
protected:
	GLuint progID;
	GLuint compileShader(GLenum type, const std::string& source);
public:
	CShader();
	virtual ~CShader();
	void createFromFileVF(const std::string& vertexShader, const std::string& fragmentShader);
	void createFromStringVF(const std::string& vertexShader, const std::string& fragmentShader);
	void bind();
	void unbind();
	GLuint getUniformLocation(const std::string& uniformName);
};

}

#endif /* CAPPLET_CSHADER_HPP_ */
