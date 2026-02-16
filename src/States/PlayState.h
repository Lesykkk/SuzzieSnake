#pragma once

#include <SFML/Audio.hpp>
#include <optional>
#include "State.h"
#include "../Entities/Field.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"

class PlayState : public State
{
public:
	PlayState(GameContext& context);

	void HandleInput(const sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw() override;
private:
	Field field;
	Snake snake;
	Food food;
	sf::View gameView;
	sf::RectangleShape outerBackground;
	bool isGameOver = false;
	bool isWin = false;

	sf::SoundBuffer eatSoundBuffer;
	std::optional<sf::Sound> eatSound;
	sf::SoundBuffer playingSoundBuffer;
	std::optional<sf::Sound> playingSound;
};