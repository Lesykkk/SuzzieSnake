#pragma once

#include <SFML/Graphics.hpp>
#include "../Game/GameContext.h"

class State
{
public:
	State(GameContext& context);
	virtual ~State() = default;

	virtual void HandleInput(const sf::Event& event) = 0;
	virtual void Update(sf::Time dt) = 0;
	virtual void Draw() = 0;
protected:
	GameContext& context;
};