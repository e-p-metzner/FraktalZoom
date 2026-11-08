// Fractal Zoom
// MIT Licence, 2026, Enrico P. Metzner

#ifndef FZ_EM_APP_MAIN_H
#define FZ_EM_APP_MAIN_H

#include "gfx/CApplet/CApplet.h"

namespace Fractal {

class FractalZoomApp : public CApplet::CApplet {
  private:

  public:
    void settings() override;
    void setup() override;
    void draw() override;
    void exit() override;
};

}

#endif /* FZ_EM_APP_MAIN_H */