#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "lodepng.h"
#include "CTexture.h"

namespace CApplet {

CTexture::CTexture(const std::string filepath) {
    id = 0;
    width = 0;
    height = 0;
    std::vector<unsigned char> image;
    unsigned w, h;
    unsigned error = lodepng::decode(image, w, h, filepath.c_str());
    if (error != 0) {
        std::cerr << "Error (" << error << ") " << lodepng_error_text(error) << std::endl;
        return;
    }
    width = w;
    height = h;

    // assume w and h are powers of 2
    // other rescaling/padding is necessary

    glGenTextures(1, &id);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
};

CTexture::~CTexture() {
    glDeleteTextures(1, &id);
};

void CTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void CTexture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

}