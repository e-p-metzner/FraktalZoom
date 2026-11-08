#ifndef CAPPLET_TEXTURE_H
#define CAPPLET_TEXTURE_H

#include <string>

namespace CApplet {

class CTexture {
private:
public:
    unsigned int id;
    int width;
    int height;
    CTexture(const std::string filepath);
    ~CTexture();
    void bind();
    void unbind();
};

} /* namespace CApplet */

#endif /* CAPPLET_TEXTURE_H */