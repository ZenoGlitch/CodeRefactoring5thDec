#pragma once
#include <unordered_map>
#include "batch.hpp"
class AssetsManagement
{
// AssetsManagment uppgift är att äga och hantera resourscer.
public:
	AssetsManagement();
	~AssetsManagement();
	
	static std::unordered_map<std::string, sf::Texture*> m_textures;
	static std::vector<std::string> m_order;
	sf::Font m_font;
	bool LoadFontFile(const std::string& filePath);
	// It set the m_font by defualt. Need to use LoadFontFile first before using SetText;
	sf::Text SetText(std::string textSentence, int size, sf::Uint32 textStyle, float positionX, float positionY);
	int GetLength();
	
	// Get texutre by name specified in loadTexture, or return null
	sf::Texture* GetTexture(std::string name);

	// Get texutre by index in map, or return null
	sf::Texture* GetTexture(int index);

	// Loads the texture and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the file, returns NULL
	sf::Texture* LoadTexture(std::string name, std::string path);

	
};