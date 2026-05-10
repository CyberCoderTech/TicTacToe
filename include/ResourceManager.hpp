#pragma once

#include<SFML/Graphics/Font.hpp>
#include<unordered_map>
#include<filesystem>


class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	sf::Font& getFont(std::filesystem::path pathFile);

private:
	std::unordered_map<std::filesystem::path, sf::Font> fontMap;
	
};

