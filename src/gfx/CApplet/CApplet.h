#ifndef CAPPLET_HPP_
#define CAPPLET_HPP_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "StandardShaders.h"

namespace CApplet {

class CApplet {
private:
	void init();
protected:
	std::string title;
	LineShader* lineDrawer;
	AreaShader* shapeDrawer;
	TextShader* textDrawer;
public:
	//fields
	int width;
	int height;
	int frameCount;
	double frameRate;
	GLFWwindow* csurface;

	//de-/constructor
	CApplet();
	virtual ~CApplet();
	//main method
	void main();
	//virtual methods
	virtual void settings();
	virtual void setup();
	virtual void draw();
	virtual void exit();
};

}

#endif /* CAPPLET_HPP_ */
