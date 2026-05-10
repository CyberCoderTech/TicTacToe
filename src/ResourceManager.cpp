#include "ResourceManager.hpp"

sf::Font& ResourceManager::getFont(std::filesystem::path pathFile)
{
    if (!fontMap.contains(pathFile)) {
        sf::Font tmpFont;
        if (!tmpFont.loadFromFile(pathFile.string())) {

        }
        fontMap[pathFile] = std::move(tmpFont);
    }
    return fontMap[pathFile];
}
