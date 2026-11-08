#ifndef STANDARD_SHADERS_H
#define STANDARD_SHADERS_H

#include "CShader.h"
#include "CTexture.h"

namespace CApplet {

class LineShader: public CShader {
private:
    int uloc_screensize;
    int uloc_color;
    int uloc_thickness;
    int uloc_relminscreen;
public:
    LineShader();
    ~LineShader();
    void setScreenSize(float width, float height);
    void setRelativeToMinScreenLength(bool b);
    void setColor(int color);
    void setThickness(float thick);
};

class AreaShader: public CShader {
private:
    int uloc_screensize;
    int uloc_fillcolor;
    int uloc_relminscreen;
public:
    AreaShader();
    ~AreaShader();
    void setScreenSize(float width, float height);
    void setFillColor(int color);
    void setRelativeToMinScreenLength(bool b);
};

class TextShader: public CShader {
private:
    unsigned int vao, vbo;
    float textsize;
    CTexture* fonttex;
    float fontwidths[256];
    int charCntX;
    int charCntY;
    int uloc_color;
    int uloc_screensize;
    int uloc_relminscreen;
public:
    TextShader();
    ~TextShader();
    void setScreenSize(float width, float height);
    void setTextColor(int color);
    void setRelativeToMinScreenLength(bool b);
    void setTextSize(float s);
    float getTextWidth(char* text);
    /** sets the font for rendering text
     * fonttexpath:      path to the font data without filextension
     * chars_per_row:    number of character colummns in the texture
     * chars_per_column: number of character rows in the texture
     */
    void setFont(std::string fonttexpath, int chars_per_row, int chars_per_column);
    /** renders text to the screen
     * text: char*, text to render on screen
     * x:    float, horizontal coordinate
     * y:    float, vertical coordinate
     * mode: int,   way how to render (0 = left, 1 = center, 2 = right)
    */
    void render(char* text, float x, float y, int mode);
};

}

#endif /* STANDARD_SHADERS_H */
