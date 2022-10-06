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

    Texture(const char* path, const char* type);
    Texture(const Texture& t);
    ~Texture();
    void activeTextureUnit(unsigned int i);
    void bindTexture();

private:
    std::string path;
    std::string type;
    void setupTexture(std::string path);
};

