#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "State.h"
#include "../Game/GameContext.h"

class GameOverState : public State
{
public:
	GameOverState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;

private:
	sf::RectangleShape overlay;
	sf::Text gameOverText;
	sf::Text promptText1;
	sf::Text promptText2;

	sf::SoundBuffer gameoverSoundBuffer;
	std::optional<sf::Sound> gameoverSound;
};