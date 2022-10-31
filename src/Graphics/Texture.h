#pragma once

class Texture
{
public:
    
    unsigned int id;

    Texture(std::string path, std::string type);
    Texture(const Texture& t);
    ~Texture();
    void activeTextureUnit(unsigned int i);
    void bindTexture();

private:
    std::string path;
    std::string type;
    void setupTexture(std::string path);
};

