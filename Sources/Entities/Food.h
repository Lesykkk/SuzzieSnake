#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <deque>
#include "../Game/GameContext.h"
#include "Field.h"

class Food
{
public:
	Food(GameContext& context, Field& field);

	void Spawn(const std::deque<sf::Vector2i>& occupiedPositions);
	void Draw();

	sf::Vector2i GetPosition() const;

private:
	GameContext& context;
	Field& field;

	sf::Vector2i position;
	sf::CircleShape shape;

	std::mt19937 rng;
};