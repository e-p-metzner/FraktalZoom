#include <signal.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "GLErrorHandler.h"
#include "CShader.h"

namespace CApplet {

CShader::CShader() {
	progID = 0;
}

CShader::~CShader() {
	if(progID==0) {
		return;
	}
	GLCall(glDeleteProgram(progID))
}

inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string CShader::readFile(const std::string& filepath) {
	HMODULE hModule = GetModuleHandle(NULL);
	if(hModule != NULL) {
		char path[MAX_PATH];
		GetModuleFileName(hModule, path, (sizeof(path)));
//		std::cout << path << std::endl;
		ownPth = path;
		std::replace( ownPth.begin(), ownPth.end(), '\\', '/' );
		ownPth = ownPth.substr(0, 1+ownPth.find_last_of("/"));
	}
	if(!exists_test1(ownPth+filepath)) {
		std::cerr << "Cannot open " << filepath << std::endl;
		raise(SIGSEGV);
	}

	std::stringstream str;
	std::ifstream stream(ownPth+filepath);
//	if(stream.is_open())
//	{
//		while(stream.peek() != EOF)
//		{
//			std::cout << (char) stream.get();
//			str << (char) stream.get();
//		}
//		std::cout << std::endl;
//		stream.close();
//		return str.str();
//	}
//	return (std::string)nullptr;
	str << stream.rdbuf();
	return str.str();
}

GLuint CShader::compileShader(GLenum type, const std::string& source) {
	GLuint sid = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(sid, 1, &src, nullptr);
	glCompileShader(sid);

	//ERROR handling...
	int result;
	glGetShaderiv(sid, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE) {
		int length;
		glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(sid, length, &length, message);
		std::cout << "Shader compilation error:" << std::endl << message << std::endl;
		glDeleteShader(sid);
		sid = 0;
		delete[] message;
	}

	return sid;
}

void CShader::createFromFileVF(const std::string& vertexShader, const std::string& fragmentShader) {
	std::string vsstr = readFile(vertexShader);
	std::string fsstr = readFile(fragmentShader);

	createFromStringVF(vsstr, fsstr);
}

void CShader::createFromStringVF(const std::string& vertexShader, const std::string& fragmentShader) {
	progID = glCreateProgram();
	GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(progID, vs);
	glAttachShader(progID, fs);
	glLinkProgram(progID);
	glValidateProgram(progID);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void CShader::bind() {
	glUseProgram(progID);
}

void CShader::unbind() {
	glUseProgram(0);
}

GLuint CShader::getUniformLocation(const std::string& uniformName) {
	glUseProgram(progID);
	GLuint loc = -1;
	GLCall(loc = glGetUniformLocation(progID, uniformName.c_str()))
	glUseProgram(0);
	return loc;
}

}

