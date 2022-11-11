#pragma once

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager* GetInstance();

	// Call in order for correct Generation
	// Materials need shaders and textures
	// GameObjects need materials
	
	void LoadAllShaders(std::string filename);
	void LoadAllTextures(std::string filename);
	void LoadAllMaterials(std::string filename);

	Shader* GetShaderByName(std::string name);
	Texture* GetTextureByName(std::string name);
	Material* GetMaterialByName(std::string name);

private:
	ResourceManager() {};
	static ResourceManager* instance;

	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Material*> materials;

	FILE* fp = nullptr;
	rapidjson::Document doc;
	void OpenFileAndGetDoc(std::string filename);
	void CloseFile();
};

