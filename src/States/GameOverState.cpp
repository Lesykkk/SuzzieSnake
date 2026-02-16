#include "GameOverState.h"

#include "PlayState.h"
#include "MenuState.h"
#include "../Game/Game.h"

GameOverState::GameOverState(GameContext& context)
	: State(context)
	, gameOverText(context.mainFont, "GAME OVER", 110)
	, promptText1(context.mainFont, "Press ENTER to restart", 44)
	, promptText2(context.mainFont, "ESC to open menu", 44)
{
	if (gameoverSoundBuffer.loadFromFile("assets/sounds/gameover.mp3"))
	{
		gameoverSound.emplace(gameoverSoundBuffer);
		gameoverSound->play();
	}
	else
	{
		throw std::runtime_error("Failed to load gameover sound!");
	}

	const float uiWidth = context.uiView.getSize().x;
	const float uiHeight = context.uiView.getSize().y;
	
	overlay.setSize({ uiWidth , uiHeight });
	overlay.setFillColor(sf::Color(0, 0, 0, 235));

	gameOverText.setFillColor(sf::Color::Red);
	promptText1.setFillColor(sf::Color::White);
	promptText2.setFillColor(sf::Color::White);
	
	sf::Vector2f uiCenter = { uiWidth / 2.f, uiHeight / 2.f };
	
	auto goBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin({ goBounds.size.x / 2.f, goBounds.size.y / 2.f });
	gameOverText.setPosition({ uiCenter.x, uiCenter.y - 50.f });

	auto prompt1Bounds = promptText1.getLocalBounds();
	promptText1.setOrigin({ prompt1Bounds.size.x / 2.f, prompt1Bounds.size.y / 2.f });
	promptText1.setPosition({ uiCenter.x, uiCenter.y + 60.f });

	auto prompt2Bounds = promptText2.getLocalBounds();
	promptText2.setOrigin({ prompt2Bounds.size.x / 2.f, prompt2Bounds.size.y / 2.f });
	promptText2.setPosition({ uiCenter.x, uiCenter.y + 120.f });
}

void GameOverState::HandleInput(const sf::Event& event)
{
	if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::Enter)
		{
			context.game.ChangeState(std::make_unique<PlayState>(context));
		}
		else if (keyEvent->code == sf::Keyboard::Key::Escape || keyEvent->code == sf::Keyboard::Key::Backspace)
		{
			context.game.ChangeState(std::make_unique<MenuState>(context));
		}
	}
}

void GameOverState::Update(sf::Time dt)
{ }

void GameOverState::Draw()
{
	context.window.setView(context.uiView);
	
	context.window.draw(overlay);
	context.window.draw(gameOverText);
	context.window.draw(promptText1);
	context.window.draw(promptText2);

	context.window.setView(context.window.getDefaultView());
}