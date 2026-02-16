#pragma once

#include "State.h"
#include <vector>
#include <SFML/Audio.hpp>
#include <optional>

enum class MenuAction
{
	Play,
	Settings,
	Exit
};

struct MenuItem
{
	MenuAction action;
	sf::Text text;

	MenuItem(MenuAction act, const sf::Font& font, const std::string& str, unsigned int size);
};

class MenuState : public State
{
public:
	MenuState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;
private:
	sf::Text titleText;
	sf::Text titleTextShadow;
	std::vector<MenuItem> items;
	int selectedIndex = 0;
	sf::Color itemColor;
	sf::Color itemColorShadow;
	sf::Color itemHoveredColor;

	sf::SoundBuffer menuSoundBuffer;
	std::optional<sf::Sound> menuSound;
};

