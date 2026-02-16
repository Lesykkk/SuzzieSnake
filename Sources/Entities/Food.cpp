#include "Food.h"

Food::Food(GameContext& context, Field& field)
	: context(context)
	, field(field)
{
	shape.setRadius(field.GetCellSize() / 2.f);
	shape.setPointCount(10);
	shape.setFillColor(sf::Color(255, 51, 51));

	std::random_device rd;
	rng.seed(rd());
}

void Food::Spawn(const std::deque<sf::Vector2i>& occupiedPositions)
{
	sf::Vector2i fieldSize = field.GetSize();

	std::uniform_int_distribution<int> distX(0, fieldSize.x - 1);
	std::uniform_int_distribution<int> distY(0, fieldSize.y - 1);

	bool validPosition = false;

	while (!validPosition)
	{
		position.x = distX(rng);
		position.y = distY(rng);

		validPosition = true;

		for (const auto& segment : occupiedPositions)
		{
			if (position == segment)
			{
				validPosition = false;
				break;
			}
		}
	}
}

void Food::Draw()
{
	float posX = position.x * field.GetCellSize();
	float posY = position.y * field.GetCellSize();

	shape.setPosition({ posX, posY });
	context.window.draw(shape);
}

sf::Vector2i Food::GetPosition() const
{
	return position;
}