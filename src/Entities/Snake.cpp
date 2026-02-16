#include "Snake.h"

Snake::Snake(GameContext& context, Field& field)
	: context(context)
	, field(field)
	, currentDirection(Direction::Right)
	, moveTimer(sf::Time::Zero)
	, moveInterval(sf::seconds(0.15f))
	, isDead(false)
	, growPending(false)
{
	sf::Vector2i startPos = { field.GetSize().x / 2, field.GetSize().y / 2 };

	body.push_back(startPos);
	body.push_back({ startPos.x - 1, startPos.y });
	body.push_back({ startPos.x - 2, startPos.y });

	bodyShape.setSize({ field.GetCellSize(), field.GetCellSize() });
	bodyShape.setFillColor(sf::Color(102, 76, 58));
}

void Snake::HandleInput(const sf::Event& event)
{
	if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		Direction lastPlannedDir = turnQueue.empty() ? currentDirection : turnQueue.back();
		
		if (turnQueue.size() < 2)
		{
			switch (keyEvent->code)
			{
			case sf::Keyboard::Key::Up:
			case sf::Keyboard::Key::W:
				if (lastPlannedDir != Direction::Down && lastPlannedDir != Direction::Up)
					turnQueue.push(Direction::Up);
				break;
			case sf::Keyboard::Key::Down:
			case sf::Keyboard::Key::S:
				if (lastPlannedDir != Direction::Up && lastPlannedDir != Direction::Down)
					turnQueue.push(Direction::Down);
				break;
			case sf::Keyboard::Key::Left:
			case sf::Keyboard::Key::A:
				if (lastPlannedDir != Direction::Right && lastPlannedDir != Direction::Left)
					turnQueue.push(Direction::Left);
				break;
			case sf::Keyboard::Key::Right:
			case sf::Keyboard::Key::D:
				if (lastPlannedDir != Direction::Left && lastPlannedDir != Direction::Right)
					turnQueue.push(Direction::Right);
				break;
			default:
				break;
			}
		}
	}
}

void Snake::Update(sf::Time dt)
{
	if (isDead) return;

	moveTimer += dt;
	if (moveTimer >= moveInterval)
	{
		moveTimer -= moveInterval;
		Move();
	}
}

void Snake::Draw()
{
	float cellSize = field.GetCellSize();
	for (const auto& segment : body)
	{
		bodyShape.setPosition({
			segment.x * cellSize,
			segment.y * cellSize
		});
		context.window.draw(bodyShape);
	}
}

void Snake::Move()
{
	if (!turnQueue.empty())
	{
		currentDirection = turnQueue.front();
		turnQueue.pop();
	}
	sf::Vector2i newHead = body.front();

	switch (currentDirection)
	{
	case Direction::Up:    newHead.y -= 1; break;
	case Direction::Down:  newHead.y += 1; break;
	case Direction::Left:  newHead.x -= 1; break;
	case Direction::Right: newHead.x += 1; break;
	case Direction::None:  return;
	}

	sf::Vector2i fieldSize = field.GetSize();

	if (newHead.x < 0)
		newHead.x = fieldSize.x - 1;
	else if (newHead.x >= fieldSize.x)
		newHead.x = 0;

	if (newHead.y < 0)
		newHead.y = fieldSize.y - 1;
	else if (newHead.y >= fieldSize.y)
		newHead.y = 0;

	body.push_front(newHead);

	if (growPending)
	{
		growPending = false;
	}
	else
	{
		body.pop_back();
	}

	if (CheckCollision())
	{
		isDead = true;
		return;
	}
}

bool Snake::CheckCollision()
{
	sf::Vector2i head = body.front();

	for (size_t i = 1; i < body.size(); ++i)
	{
		if (body[i] == head)
		{
			return true;
		}
	}

	return false;
}

bool Snake::IsDead() const
{
	return isDead;
}

void Snake::Grow()
{
	growPending = true;
}

sf::Vector2i Snake::GetHeadPosition() const
{
	return body.front();
}

const std::deque<sf::Vector2i>& Snake::GetBody() const
{
	return body;
}