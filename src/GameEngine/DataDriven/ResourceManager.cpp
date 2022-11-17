#include "pch.h"

ResourceManager* ResourceManager::instance = nullptr;
ResourceManager* ResourceManager::GetInstance()
{
	static ResourceManager* instance = new ResourceManager();
	return instance;
}
ResourceManager::~ResourceManager()
{
	delete instance;
}

void ResourceManager::LoadAllShaders(std::string filename)
{
	TraceMessage("Load Shaders:");
	OpenFileAndGetDoc(filename);
	rapidjson::Value& shadersInJson = doc.FindMember(JSONConstants::SHADERS)->value;
	for (rapidjson::Value::ConstMemberIterator itr = shadersInJson.MemberBegin(); itr != shadersInJson.MemberEnd(); ++itr)
	{
		const rapidjson::Value& thisShader = itr->value;
		Shader* temp = new Shader();
		temp->Deserialize(thisShader);
		shaders[temp->GetName()]=temp;
		TraceMessage(temp->GetName().c_str());
	}
	CloseFile();
}
void ResourceManager::LoadAllTextures(std::string filename)
{
	TraceMessage("Load Textures:");
	OpenFileAndGetDoc(filename);
	rapidjson::Value& texturesInJson = doc.FindMember(JSONConstants::TEXTURES)->value;
	for (rapidjson::Value::ConstMemberIterator itr = texturesInJson.MemberBegin(); itr != texturesInJson.MemberEnd(); ++itr)
	{
		const rapidjson::Value& thisTexture = itr->value;
		Texture* temp = new Texture();
		temp->Deserialize(thisTexture);
		textures[temp->GetName()]=temp;
		TraceMessage(temp->GetName().c_str());
	}
	CloseFile();
}
void ResourceManager::LoadAllMaterials(std::string filename)
{
	TraceMessage("Load Materials:");
	OpenFileAndGetDoc(filename);
	rapidjson::Value& materialsInJson = doc.FindMember(JSONConstants::MATERIALS)->value;
	for (rapidjson::Value::ConstMemberIterator itr = materialsInJson.MemberBegin(); itr != materialsInJson.MemberEnd(); ++itr)
	{
		const rapidjson::Value& thisMaterial = itr->value;
		Material* temp = new Material();
		std::string name = thisMaterial.FindMember(JSONConstants::MATERIAL_NAME)->value.GetString();
		temp->SetName(name);
		auto colorArray = thisMaterial.FindMember(JSONConstants::COLOR)->value.GetArray();
		std::string shaderToAttach = thisMaterial.FindMember(JSONConstants::SHADER)->value.GetString();
		std::string textureToAttach = thisMaterial.FindMember(JSONConstants::TEXTURE)->value.GetString();
		temp->SetColor(colorArray[0].GetFloat(), colorArray[1].GetFloat(), colorArray[2].GetFloat(), colorArray[3].GetFloat());
		temp->AttachShader(GetShaderByName(shaderToAttach));
		temp->AttachTexture(GetTextureByName(textureToAttach));
		materials[temp->GetName()] = temp;
		TraceMessage(temp->GetName().c_str());
	}
	CloseFile();
}

void ResourceManager::UnloadAllResources()
{
	for (std::unordered_map<std::string, Material*>::iterator itr = materials.begin();
		itr != materials.end(); itr++)
	{
		delete itr->second;
	}
	for (std::unordered_map<std::string, Texture*>::iterator itr = textures.begin();
		itr != textures.end(); itr++)
	{
		delete itr->second;
	}
	for (std::unordered_map<std::string, Shader*>::iterator itr = shaders.begin();
		itr != shaders.end(); itr++)
	{
		delete itr->second;
	}
}

Shader* ResourceManager::GetShaderByName(std::string name)
{
	if (shaders.find(name) != shaders.end())
	{
		return shaders[name];
	}
	std::string str = "Shader not found in ResourceManager:" + name;
	TraceMessage(str.c_str());
	exit(EXIT_FAILURE);
}
Texture* ResourceManager::GetTextureByName(std::string name)
{
	if (textures.find(name) != textures.end())
	{
		return textures[name];
	}
	std::string str = "Texture not found in ResourceManager" + name;
	TraceMessage(str.c_str());
	exit(EXIT_FAILURE);
}
Material* ResourceManager::GetMaterialByName(std::string name)
{
	if (materials.find(name) != materials.end())
	{
		return materials[name];
	}
	std::string str = "Material not found in ResourceManager" + name;
	TraceMessage(str.c_str());
	exit(EXIT_FAILURE);
}

// helpers
void ResourceManager::OpenFileAndGetDoc(std::string filename)
{
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp)
	{
		std::string str = "File not found: " + filename;
		TraceMessage(str.c_str());
		exit(EXIT_FAILURE);
	}
	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(inputStream);
}
void ResourceManager::CloseFile()
{
	fclose(fp);
}

