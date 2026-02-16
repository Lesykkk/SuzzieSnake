#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>
#include <string>
#include <functional>
#include "State.h"
#include "../Game/GameContext.h"

class SettingsState : public State
{
public:
	SettingsState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;

private:
	struct MenuItem
	{
		sf::Text text;
		std::function<void()> onLeft;
		std::function<void()> onRight;
		std::function<std::string()> getText;
	};

	sf::Text titleText;
	sf::Text hintText;

	std::vector<sf::Text> categoryHeaders;
	std::vector<MenuItem> items;

	std::vector<sf::VideoMode> videoModes;
	int currentModeIndex = 0;

	int selectedIndex = 0;
	sf::SoundBuffer menuSoundBuffer;
	std::optional<sf::Sound> menuSound;
	ConfigData localConfig;

	void UpdateSelection();
	void UpdateTexts();
	void AddItem(float x, float y, std::function<void()> onLeft, std::function<void()> onRight, std::function<std::string()> getText);
};