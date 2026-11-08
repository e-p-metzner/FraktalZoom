#include <GL/glew.h>

#include "CShape.h"

#ifndef CSHAPE_2D_H
#define CSHAPE_2D_H

namespace CApplet {

namespace CShape2D {

CShape* linestrip(int vcount, float* vcoords);
CShape* ellipse(float cx, float cy, float rx, float ry, int num_points, bool filled);
CShape* rect(float x0, float y0, float x1, float y1, bool filled);
CShape* quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, bool filled);

} /* namespace CShape2D */

} /* namespace CApplet */

#endif /* CSHAPE_2D_H */