// Fractal Zoom
// MIT Licence, 2026, Enrico P. Metzner

#include "AppMain.h"

int main(int argc, char **argv)
{
    Fractal::FractalZoomApp* app;
    app = new Fractal::FractalZoomApp();
    app->main();
}


namespace Fractal {

void FractalZoomApp::settings() {
    width = 1280;
    height = 800;
}

void FractalZoomApp::setup() {

}

void FractalZoomApp::draw() {

}

void FractalZoomApp::exit() {

}

}