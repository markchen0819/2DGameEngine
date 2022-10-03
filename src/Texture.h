#pragma once
#include <GLEW/include/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <string>
#include <iostream>

class Texture
{
public:
    
    unsigned int id;
    std::string path;
    std::string type;

    Texture(const char* path, const char* type);
    ~Texture();
    void activeTextureUnit(unsigned int i);
    void bind();

private:

    void setupTexture(std::string path);
};

