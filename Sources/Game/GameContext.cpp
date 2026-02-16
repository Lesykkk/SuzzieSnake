#include "GameContext.h"

GameContext::GameContext(Game& game, sf::RenderWindow& window, ConfigData& config, ConfigManager& configManager, sf::View& uiView, sf::Font& mainFont, std::string& title, sf::Color mainColor, sf::Color mainColorShadow, sf::Color accentColor)
	: game(game)
	, window(window)
	, config(config)
	, configManager(configManager)
	, uiView(uiView)
	, mainFont(mainFont)
	, title(title)
	, mainColor(mainColor)
	, mainColorShadow(mainColorShadow)
	, accentColor(accentColor)
{ }