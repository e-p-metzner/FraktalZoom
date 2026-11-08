#include <iostream>
#include <chrono>
#include <cmath>

#include "CApplet.h"

namespace CApplet {

CApplet::CApplet() {
	width = 0;
	height = 0;
	title = "OpenGL Test";
	frameCount = 0;
	frameRate = 0.0;
	csurface = nullptr;
    lineDrawer = nullptr;
    shapeDrawer = nullptr;
    textDrawer = nullptr;
}

CApplet::~CApplet() {
    if(lineDrawer)
        delete lineDrawer;
    if(shapeDrawer)
        delete shapeDrawer;
    if(textDrawer)
        delete textDrawer;
}

void CApplet::main() {
	settings();
	if(width<=0 || height<0) {
		std::cerr << "Window width and height have to be larger than 0!" << std::endl;
		return;
	}

	init();

    lineDrawer = new LineShader();
    shapeDrawer = new AreaShader();
    textDrawer = new TextShader();

	setup();

    frameCount = 0;
    auto t_start = std::chrono::steady_clock::now();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(csurface))
    {
    	glfwGetWindowSize(csurface, &width, &height);
    	glViewport(0, 0, width, height);

        /* Render here */
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(csurface);

        /* Poll for and process events */
        glfwPollEvents();

		auto t_end = std::chrono::steady_clock::now();
		uint64_t delta = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end-t_start).count();
		if(delta < 1)
			delta = 1;
		frameRate = 1000000000.0 / delta;
		t_start = t_end;
		frameCount++;

        if(glfwGetKey(csurface, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(csurface, true);
    }

	exit();

    glfwTerminate();
}

void CApplet::settings() { }

void CApplet::setup() { }

void CApplet::draw() { }

void CApplet::exit() { }

//////////////////////////////////////////////////////////////////////

void CApplet::init() {
    /* Initialize the library */
    if (!glfwInit()) {
    	std::cerr << "Error during GLFW initialization." << std::endl;
        return;
    }
    /* Create a windowed mode window and its OpenGL context */
    csurface = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!csurface)
    {
        glfwTerminate();
        std::cerr << "Could not create window." << std::endl;
        return;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(csurface);
    glfwSetWindowSizeLimits(csurface, 120,120, 4096,3720);

    if(glewInit() != GLEW_OK) {
    	std::cerr << "Cannot initialize GLEW!" << std::endl;
        glfwTerminate();
    	return;
    }

    glEnable(GL_PROGRAM_POINT_SIZE);
    glfwSetWindowTitle(csurface, title.c_str());
}

}
