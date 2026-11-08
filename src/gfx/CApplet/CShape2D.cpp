#include <cmath>

#include "CShape2D.h"

#define PI  3.14159265359
#define TAU 6.28318530718

namespace CApplet {

namespace CShape2D {

CShape* linestrip(int vcount, float* vcoords) {
    unsigned int* indeces = new unsigned int[2*vcount-2];
    CShape* s = new CShape();
    s->bind();
    s->storeFloats(0, 2, vcount, vcoords);
    for(int i=1; i<vcount; i++) {
        indeces[2*i-2] = i-1;
        indeces[2*i-1] = i;
    }
    s->storeIndeces(2*vcount-2, indeces);
    s->unbind(false);
    delete indeces;
    return s;
}

CShape* ellipse(float cx, float cy, float rx, float ry, int num_points, bool filled) {
    int vcnt = 2*num_points;
    float* vertices = new float[vcnt];
    int icnt = filled ? 3*(num_points-2) : 2*num_points;
    unsigned int* indeces = new unsigned int[filled];
    for(int i=0; i<num_points; i++) {
        double a = i * TAU / num_points;
        vertices[2*i+0] = cx - rx * (float)std::cos(a);
        vertices[2*i+1] = cy + ry * (float)std::sin(a);
    }
    if(filled) {
        for(int i=0; i<num_points-2; i++) {
            indeces[3*i+0] = 0;
            indeces[3*i+1] = i+1;
            indeces[3*i+2] = i+2;
        }
    } else {
        for(int i=0; i<num_points; i++) {
            indeces[2*i+0] = i;
            indeces[2*i+1] = (i+1) % num_points;
        }
    }
    CShape* s = new CShape();
    s->bind();
    s->storeFloats(0, 2, num_points, vertices);
    s->storeIndeces(icnt, indeces);
    s->unbind(false);
    delete vertices;
    delete indeces;
    return s;
}

CShape* rect(float x0, float y0, float x1, float y1, bool filled) {
    return quad(x0, y0, x1, y0, x1, y1, x0, y1, filled);
}

CShape* quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, bool filled) {
    float vertices[8] = { x0, y0, x1, y1, x2, y2, x3, y3 };
    unsigned int lineIdx[8] = { 0, 1, 1, 2, 2, 3, 3, 0 };
    unsigned int areaIdx[6] = { 0, 1, 3, 3, 1, 2 };
    CShape* s = new CShape();
    s->bind();
    s->storeFloats(0, 2, 4, vertices);
    s->storeIndeces(filled ? 6 : 8, filled ? areaIdx : lineIdx);
    s->unbind(false);
    return s;
}

} /* namespace CShape2D */

} /* namespace CApplet */