#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <queue>
#include "../Game/GameContext.h"
#include "Field.h"

class Snake
{
public:
	Snake(GameContext& context, Field& field);

	void HandleInput(const sf::Event& event);
	void Update(sf::Time dt);
	void Draw();

	bool IsDead() const;
	void Grow();

	sf::Vector2i GetHeadPosition() const;
	const std::deque<sf::Vector2i>& GetBody() const;
private:
	void Move();
	bool CheckCollision();

	GameContext& context;
	Field& field;

	enum class Direction { Up, Down, Left, Right, None };
	Direction currentDirection;
	std::queue<Direction> turnQueue;

	std::deque<sf::Vector2i> body;

	sf::Time moveTimer;
	sf::Time moveInterval;

	bool isDead;
	bool growPending;

	sf::RectangleShape bodyShape;
};