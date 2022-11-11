#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

Texture::Texture()
{
	// use Deserialize to generate texture
}
Texture::Texture(std::string path, std::string type)
{
	this->path = path;
	this->type = type;
	setupTexture(this->path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}
Texture::Texture(const Texture& t) // Copy ctor
{
	this->path = t.path;
	this->type = t.type;
	setupTexture(path); // when passed as a copy we need a new id
}
void Texture::setupTexture(std::string path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 100);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		TraceMessage("Failed to load texture");
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activeTextureUnit(unsigned int i)
{
	glActiveTexture(GL_TEXTURE0 + i);
}
void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, id);
}


void Texture::Serialize()
{
}

void Texture::Deserialize(const rapidjson::Value& obj)
{
	Name = obj.FindMember(JSONConstants::TEXTURE_NAME)->value.GetString();
	this->path = obj.FindMember(JSONConstants::TEXTURE_FILE)->value.GetString();
	this->type = obj.FindMember(JSONConstants::TEXTURETYPE)->value.GetString();

	this->path = path;
	this->type = type;
	setupTexture(this->path);
}

void Texture::SetName(std::string name)
{
	Name = name;
}

std::string Texture::GetName()
{
	return Name;
}
