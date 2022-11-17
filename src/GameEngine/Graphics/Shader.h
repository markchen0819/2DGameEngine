#pragma once

class Shader
{
public:

    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void useProgram();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const; 
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void Serialize();
    void Deserialize(const rapidjson::Value& obj);
    void SetName(std::string name);
    std::string GetName();

private:
    unsigned int ID;
    std::string Name="";
    void compileProgram(const char* vertexPath, const char* fragmentPath);
    void checkCompileErrors(unsigned int shader, std::string type);
};
