#pragma once

#include <SFML/Graphics.hpp>
#include "../Game/GameContext.h"

class Field
{
public:
	Field(GameContext& context);

	void Draw();
	sf::Vector2i GetSize() const;
	float GetCellSize() const;
	unsigned int GetHeightCellNumber() const;
	bool IsOutOfBounds(int gridX, int gridY) const;
private:
	GameContext& context;
	const float CELL_SIZE = 32.f;
	const unsigned int HEIGHT_CELL_NUMBER = 20u;
	const unsigned int GAP_CELL_NUMBER = 1u;
	int gridColumns;
	int gridRows;
	sf::RectangleShape playArea;
};

