#include "Field.h"
#include <cmath>

Field::Field(GameContext& context)
	: context(context)
{
	float windowWidth = static_cast<float>(context.window.getSize().x);
	float windowHeight = static_cast<float>(context.window.getSize().y);
	float aspectRatio = windowWidth / windowHeight;

	float viewHeightPx = HEIGHT_CELL_NUMBER * CELL_SIZE;
	float viewWidthPx= viewHeightPx * aspectRatio;

	gridColumns = static_cast<int>(std::floor(viewWidthPx / CELL_SIZE)) - (GAP_CELL_NUMBER * 2);
	gridRows = HEIGHT_CELL_NUMBER - (GAP_CELL_NUMBER * 2);

	float gridColumnsPx = gridColumns * CELL_SIZE;
	float gridRowsPx = gridRows * CELL_SIZE;

	playArea.setSize({ gridColumnsPx, gridRowsPx });
	playArea.setPosition({ 0.f, 0.f });
	playArea.setFillColor(sf::Color(114, 191, 96));
}

void Field::Draw()
{
	context.window.draw(playArea);
}

sf::Vector2i Field::GetSize() const
{
	return { gridColumns, gridRows };
}

float Field::GetCellSize() const
{
	return CELL_SIZE;
}

unsigned int Field::GetHeightCellNumber() const
{
	return HEIGHT_CELL_NUMBER;
}

bool Field::IsOutOfBounds(int gridX, int gridY) const
{
	return gridX < 0 || gridX >= gridColumns || gridY < 0 || gridY >= gridRows;
}