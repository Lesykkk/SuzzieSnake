#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"

class Game;

struct GameContext
{
	Game& game;
	sf::RenderWindow& window;
	ConfigData& config;
	ConfigManager& configManager;
	sf::View& uiView;
	sf::Font& mainFont;
	std::string& title;
	sf::Color mainColor;
	sf::Color mainColorShadow;
	sf::Color accentColor;

	GameContext(
		Game& game,
		sf::RenderWindow& window,
		ConfigData& config,
		ConfigManager& configManager,
		sf::View& uiView,
		sf::Font& mainFont,
		std::string& title,
		sf::Color mainColor,
		sf::Color mainColorShadow,
		sf::Color accentColor
	);
};