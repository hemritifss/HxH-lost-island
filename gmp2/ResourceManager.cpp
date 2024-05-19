#include "ResourceManager.hpp"

namespace HxH {

    // Load a texture from file and store it in the map
    void ResourceManager::LoadTexture(const std::string& name, const std::string& fileName) {
        sf::Texture tex;
        if (tex.loadFromFile(fileName)) {
            this->_textures[name] = tex;
        }
    }

    // Get a reference to a stored texture
    sf::Texture& ResourceManager::GetTexture(const std::string& name) {
        return this->_textures.at(name);
    }

    // Load a font from file and store it in the map
    void ResourceManager::LoadFont(const std::string& name, const std::string& fileName) {
        sf::Font font;
        if (font.loadFromFile(fileName)) {
            this->_fonts[name] = font;
        }
    }

    // Get a reference to a stored font
    sf::Font& ResourceManager::GetFont(const std::string& name) {
        return this->_fonts.at(name);
    }
}
