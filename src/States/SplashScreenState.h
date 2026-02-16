#pragma once

#include "State.h"
#include <SFML/Audio.hpp>

class SplashScreenState : public State
{
public:
	SplashScreenState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;
private:
	sf::Text titleText;
	sf::Text titleTextShadow;
	sf::Time elapsedTime;
	sf::Time displayDuration;

	sf::SoundBuffer splashSoundBuffer;
	std::optional<sf::Sound> splashSound;
};