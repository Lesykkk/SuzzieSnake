#include "PlayState.h"

#include "GameOverState.h"
#include "WinState.h"
#include "MenuState.h"
#include "../Game/Game.h"
//#include <iostream>

PlayState::PlayState(GameContext& context)
	: State(context)
	, field(context)
	, snake(context, field)
	, food(context, field)
{
	if (eatSoundBuffer.loadFromFile("assets/sounds/eat.mp3"))
	{
		eatSound.emplace(eatSoundBuffer);
	}
	else
	{
		throw std::runtime_error("Failed to load eat sound!");
	}

	if (playingSoundBuffer.loadFromFile("assets/sounds/playing.mp3"))
	{
		playingSound.emplace(playingSoundBuffer);
		playingSound->setVolume(30.f);
		playingSound->setLooping(true);
		playingSound->play();
	}
	else
	{
		throw std::runtime_error("Failed to load playing sound!");
	}
	
	float windowWidth = static_cast<float>(context.window.getSize().x);
	float windowHeight = static_cast<float>(context.window.getSize().y);
	float aspectRatio = windowWidth / windowHeight;

	float viewHeightPx = field.GetHeightCellNumber() * field.GetCellSize();
	float viewWidthPx = viewHeightPx * aspectRatio;

	float fieldWidthPx = field.GetSize().x * field.GetCellSize();
	float fieldHeigthPx = field.GetSize().y * field.GetCellSize();

	float paddingX = (viewWidthPx - fieldWidthPx) / 2.0f;
	float paddingY = (viewHeightPx - fieldHeigthPx) / 2.0f;

	gameView.setSize({ viewWidthPx, viewHeightPx });

	gameView.setCenter({
		viewWidthPx / 2.0f - paddingX,
		viewHeightPx / 2.0f - paddingY
		});

	outerBackground.setSize({ viewWidthPx, viewHeightPx });
	outerBackground.setPosition({ -paddingX, -paddingY });
	outerBackground.setFillColor(sf::Color::Black);

	food.Spawn(snake.GetBody());
}

void PlayState::HandleInput(const sf::Event& event)
{
	if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::Escape || keyEvent->code == sf::Keyboard::Key::Backspace)
		{
			context.game.ChangeState(std::make_unique<MenuState>(context));
			return;
		}
	}

	snake.HandleInput(event);
}

void PlayState::Update(sf::Time dt)
{
	if (isGameOver) return;
	if (isWin) return;

	snake.Update(dt);

	if (snake.IsDead())
	{
		isGameOver = true;
		playingSound->stop();
		context.game.PushState(std::make_unique<GameOverState>(context));
		return;
	}

	if (snake.GetBody().size() == static_cast<size_t>(field.GetSize().x * field.GetSize().y))
	{
		isWin = true;
		playingSound->stop();
		context.game.PushState(std::make_unique<WinState>(context));
		return;
	}

	if (snake.GetHeadPosition() == food.GetPosition())
	{
		snake.Grow();
		eatSound->play();
		food.Spawn(snake.GetBody());
		//std::cout << "Food eaten!" <<std::endl;
		//std::cout << "Snake length: " << snake.GetBody().size() + 1 << std::endl;
		//std::cout << "Field length: " << field.GetSize().x * field.GetSize().y << std::endl;
	}
}

void PlayState::Draw()
{
	context.window.setView(gameView);

	context.window.draw(outerBackground);
	field.Draw();
	food.Draw();
	snake.Draw();

	context.window.setView(context.window.getDefaultView());
}