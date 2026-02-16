#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "State.h"
#include "../Game/GameContext.h"

class WinState : public State
{
public:
	WinState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;

private:
	sf::RectangleShape overlay;
	sf::Text winText;
	sf::Text promptText1;
	sf::Text promptText2;

	sf::SoundBuffer winSoundBuffer;
	std::optional<sf::Sound> winSound;
};