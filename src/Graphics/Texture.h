#pragma once

class Texture
{
public:
    
    unsigned int id;

    Texture();

    Texture(std::string path, std::string type);
    Texture(const Texture& t);
    ~Texture();
    void activeTextureUnit(unsigned int i);
    void bindTexture();

    void Serialize();
    void Deserialize(const rapidjson::Value& obj);
    void SetName(std::string name);
    std::string GetName();

private:
    std::string Name = "";
    std::string path;
    std::string type;
    void setupTexture(std::string path);

};

