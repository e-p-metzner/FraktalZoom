#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <nlohmann/json.hpp>
#include "GLErrorHandler.h"
#include "StandardShaders.h"

using json = nlohmann::json;

namespace CApplet {

#define LINE2DVERT \
"#version 330 core\n\n"\
"layout(location = 0) in vec2 pos; "\
"uniform vec2 screen; "\
"uniform int relative; "\
"void main() { "\
"if(relative == 0) { "\
"gl_Position = vec4(pos.xy/screen, 0.0, 1.0); "\
"} else { "\
"gl_Position = vec4(pos.xy, 0.0, 1.0); "\
"} "\
"}"

#define LINE2DGEOM \
"#version 330 core\n\n"\
"layout(lines) in; "\
"layout(triangle_strip, max_vertices = 4) out; "\
"uniform vec2 screen; "\
"uniform float line_width; "\
"void main() { "\
"float ar = sqrt(screen.y / screen.x); "\
"vec4 lw = vec4(ar, 1.0/ar, 0.0, 0.0) * line_width / min(screen.x, screen.y); "\
"vec2 ndc_a = gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w; "\
"vec2 ndc_b = gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w; "\
"vec2 line_vector = 0.5 * normalize((ndc_b - ndc_a) * screen); "\
"vec4 nor = vec4(-line_vector.y, line_vector.x, 0.0, 0.0) * lw; "\
"vec4 dir = vec4(line_vector, 0.0, 0.0) * lw; "\
"gl_Position = gl_in[0].gl_Position - dir - nor; "\
"EmitVertex(); "\
"gl_Position = gl_in[0].gl_Position - dir + nor; "\
"EmitVertex(); "\
"gl_Position = gl_in[1].gl_Position + dir - nor; "\
"EmitVertex(); "\
"gl_Position = gl_in[1].gl_Position + dir + nor; "\
"EmitVertex(); "\
"EndPrimitive(); "\
"}"

#define LINE2DFRAG \
"#version 330 core\n\n"\
"uniform vec4 color;\n"\
"out vec4 frag_color; "\
"void main() { "\
"frag_color = color; "\
"}"

LineShader::LineShader() {
    progID = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, LINE2DVERT);
    GLuint gs = compileShader(GL_GEOMETRY_SHADER, LINE2DGEOM);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, LINE2DFRAG);
	glAttachShader(progID, vs);
    glAttachShader(progID, gs);
	glAttachShader(progID, fs);
	glLinkProgram(progID);
	glValidateProgram(progID);
	glDeleteShader(vs);
    glDeleteShader(gs);
	glDeleteShader(fs);
    unbind();

    bind();
    uloc_color = getUniformLocation("color");
    uloc_relminscreen = getUniformLocation("relative");
    uloc_screensize = getUniformLocation("screen");
    uloc_thickness = getUniformLocation("line_width");
    unbind();
}

LineShader::~LineShader() {
	if(progID==0) {
		return;
	}
	GLCall(glDeleteProgram(progID))
}

void LineShader::setScreenSize(float width, float height) {
    if(uloc_screensize>0)
        GLCall(glUniform2f(uloc_screensize, width, height))
}

void LineShader::setRelativeToMinScreenLength(bool b) {
    if(uloc_relminscreen>0)
        GLCall(glUniform1i(uloc_relminscreen, b ? 1 : 0))
}

void LineShader::setColor(int color) {
    int a = (color>>24) & 255;
    int r = (color>>16) & 255;
    int g = (color>>8) & 255;
    int b = color & 255;
    GLCall(glUniform4f(uloc_color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f))
}

void LineShader::setThickness(float thick) {
    GLCall(glUniform1f(uloc_thickness, thick))
}




#define AREAVERT \
"#version 330 core\n\n"\
"layout(location = 0) in vec2 pos; "\
"uniform vec2 screen; "\
"uniform int relative; "\
"void main() { "\
"if(relative == 0) { "\
"gl_Position = vec4(pos.xy/screen, 0.0, 1.0); "\
"} else { "\
"gl_Position = vec4(pos.xy, 0.0, 1.0); "\
"} "\
"}"

#define AREAFRAG \
"#version 330 core\n\n"\
"uniform vec4 color; "\
"out vec4 frag_color; "\
"void main() { "\
"frag_color = color; "\
"}"

AreaShader::AreaShader() {
    createFromStringVF(AREAVERT, AREAFRAG);
    bind();
    uloc_screensize = getUniformLocation("screen");
    uloc_relminscreen = getUniformLocation("relative");
    uloc_fillcolor = getUniformLocation("color");
    unbind();
}

AreaShader::~AreaShader() {
	if(progID==0) {
		return;
	}
	GLCall(glDeleteProgram(progID))
}

void AreaShader::setScreenSize(float width, float height) {
    GLCall(glUniform2f(uloc_screensize, width, height))
}

void AreaShader::setRelativeToMinScreenLength(bool b) {
    GLCall(glUniform1i(uloc_relminscreen, b ? 1 : 0))
}

void AreaShader::setFillColor(int color) {
    int a = (color>>24) & 255;
    int r = (color>>16) & 255;
    int g = (color>>8) & 255;
    int b = color & 255;
    GLCall(glUniform4f(uloc_fillcolor, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f))
}




#define TEXTVERT \
"#version 330 core\n\n"\
"layout(location = 0) in vec4 pos; "\
"uniform vec2 screen; "\
"uniform int relative; "\
"out vec2 uv; "\
"void main() { "\
"if(relative == 0) { "\
"gl_Position = vec4(pos.xy/screen, 0.0, 1.0); "\
"} else { "\
"gl_Position = vec4(pos.xy, 0.0, 1.0); "\
"}\n"\
"uv = pos.zw; "\
"}"

#define TEXTFRAG \
"#version 330 core\n\n"\
"in vec2 uv; "\
"uniform vec4 color; "\
"uniform sampler2D tex; "\
"out vec4 frag_color; "\
"void main() { "\
"vec4 col = texture(tex, uv) * color; "\
"if(col.a<0.001) discard; "\
"frag_color = col; "\
"}"

TextShader::TextShader() {
    createFromStringVF(TEXTVERT, TEXTFRAG);
    bind();
    uloc_screensize = getUniformLocation("screen");
    uloc_relminscreen = getUniformLocation("relative");
    uloc_color = getUniformLocation("color");
    unbind();
    textsize = 0.0f;
    charCntX = 0;
    charCntY = 0;
    fonttex = nullptr;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24*sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextShader::~TextShader() {
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
	if(progID==0) {
		return;
	}
	GLCall(glDeleteProgram(progID))
    if(fonttex)
        delete fonttex;
}

void TextShader::setScreenSize(float width, float height) {
    GLCall(glUniform2f(uloc_screensize, width, height))
}

void TextShader::setRelativeToMinScreenLength(bool b) {
    GLCall(glUniform1i(uloc_relminscreen, b ? 1 : 0))
}

void TextShader::setTextColor(int color) {
    int a = (color>>24) & 255;
    int r = (color>>16) & 255;
    int g = (color>>8) & 255;
    int b = color & 255;
    GLCall(glUniform4f(uloc_color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f))
}

void TextShader::setTextSize(float s) {
    textsize = s;
}

void TextShader::setFont(std::string fonttexpath, int chars_per_row, int chars_per_column) {
    if (fonttex)
        delete fonttex;
    fonttex = new CTexture(fonttexpath+std::string(".png"));
    charCntX = chars_per_row;
    charCntY = chars_per_column;
    for(int i=0; i<256; i++)
        fontwidths[i] = 0.0f;
    try {
        std::ifstream f(fonttexpath+std::string(".json"));
        json data = json::parse(f).at("widths");
        int i=0;
        for(auto &entry : data) {
            if(i>=256) break;
            fontwidths[i] = entry.get_to(fontwidths[i]);
            i++;
        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    }
}

float TextShader::getTextWidth(char* text) {
    int clen = strlen(text);
    float w = 0.0f;
    for(int i=0; i<clen; i++) {
        int c_id = (int)(unsigned char)text[i];
        if(c_id<0 || c_id>255) continue;
        w += fontwidths[c_id];
    }
    return textsize * w;
}

void TextShader::render(char* text, float x, float y, int mode) {
    if (!fonttex)
        return;
    // activate corresponding render state
    glActiveTexture(GL_TEXTURE0);
    fonttex->bind();
    glBindVertexArray(vao);

    // iterate through all characters
    int cl = strlen(text);
    char start[2] = {text[0],'\0'};
    float xpos = x - 0.5f*textsize + 0.5f*getTextWidth(start);
    float ypos = y - 0.5f*textsize;
    switch(mode) {
        default:
        case 0:
            break;
        case 1:
            xpos -= 0.5f*getTextWidth(text);
            break;
        case 2:
            xpos -= getTextWidth(text);
            break;
    }
    float tx = 0.0;
    float ty = 0.0;
    float tw = 1.0f / charCntX;
    float th = 1.0f / charCntY;
    for (int ci = 0; ci < cl; ci++) {
        int c_id = (int)(unsigned char)(text[ci]);
        tx = (c_id % charCntX) * tw;
        ty = (c_id / charCntX) * th;

        float vertices[24] = {
            xpos,            ypos + textsize,   tx,    ty,
            xpos,            ypos,              tx,    ty+th,
            xpos + textsize, ypos,              tx+tw, ty+th,
            xpos,            ypos + textsize,   tx,    ty,
            xpos + textsize, ypos,              tx+tw, ty+th,
            xpos + textsize, ypos + textsize,   tx+tw, ty
        };

        // render glyph texture over quad
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        if(c_id<0 || c_id>255) continue;
        xpos += textsize * fontwidths[c_id];
    }
    glBindVertexArray(0);
    fonttex->unbind();
}

}