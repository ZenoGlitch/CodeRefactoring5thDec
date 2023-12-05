#include "AssetsManagment.h"

// Most of the method and logic from another project

AssetsManagement::AssetsManagement()
{
   
};

AssetsManagement::~AssetsManagement()
{
    // Delete all of the textures we used
    sf::Texture* texture;
    std::unordered_map<std::string, sf::Texture*>::iterator iter = m_textures.begin();
    while (iter != m_textures.end())
    {
        texture = iter->second;
        delete texture;
        iter++;
    }

};

std::unordered_map< std::string, sf::Texture* > AssetsManagement::m_textures;
std::vector<std::string> AssetsManagement::m_order;
std::unordered_map < std::string, sf::Text*> m_text;
bool AssetsManagement::LoadFontFile(const std::string& filePath)
{
    if(!m_font.loadFromFile(filePath))
    {
        //error
        return false;
    }
    return true;
}

sf::Text AssetsManagement::SetText(std::string textSentence, int size, sf::Uint32 textStyle, float positionX, float positionY)
{
    sf::Text text;
    //Have m_font as defualt font.
    text.setFont(m_font);
    text.setCharacterSize(size);
    text.setStyle(textStyle);
    text.setPosition(positionX, positionY);
    text.setString(textSentence);
    return text;
}

int AssetsManagement::GetLength()
{
    int size = static_cast<int>(m_textures.size());
	return size;
}

// Get Texture by Name
sf::Texture* AssetsManagement::GetTexture(std::string name)
{

    // See if we have already loaded this texture
    if (m_textures.find(name) != m_textures.end()) {
        return m_textures[name];
    }
    else {
        return NULL;
    }
}

// Get Texture by Index
sf::Texture* AssetsManagement::GetTexture(int index)
{
    // Stay DRY and reuse get by name, but get string name from vector with index
    return GetTexture(m_order.at(index));
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture* AssetsManagement::LoadTexture(std::string name, std::string path)
{
    // Haven't loaded it yet, time to create it
    sf::Texture* texture = new sf::Texture();

    if (texture->loadFromFile(path))
    {
        m_textures[name] = texture;

        // Push to vector the order in which items were loaded into map, for accessing via index.
        m_order.push_back(name);
        return m_textures[name];
    }
    else
    {
        // Could not load the file
        delete texture;
        return NULL;
    }

}