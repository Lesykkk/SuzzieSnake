#include "SplashScreenState.h"

#include "../Game/Game.h"
#include "MenuState.h"

SplashScreenState::SplashScreenState(GameContext& context)
	: State(context)
	, titleText(context.mainFont, context.title, 80)
	, titleTextShadow(context.mainFont, context.title, 80)
	, elapsedTime(sf::Time::Zero)
	, displayDuration(sf::seconds(2.0f))
{	
	if (splashSoundBuffer.loadFromFile("assets/sounds/splash.mp3"))
	{
		splashSound.emplace(splashSoundBuffer);
		splashSound->play();
	}
	else
	{
		throw std::runtime_error("Failed to load splash sound!");
	}

	const float uiWidth = context.uiView.getSize().x;
	const float uiHeight = context.uiView.getSize().y;
	
	titleText.setFillColor(context.mainColor);
	titleTextShadow.setFillColor(context.mainColorShadow);

	sf::FloatRect titleBounds = titleText.getLocalBounds();
	titleText.setOrigin({
		titleBounds.position.x + titleBounds.size.x / 2.0f,
		titleBounds.position.y + titleBounds.size.y / 2.0f
	});
	titleTextShadow.setOrigin({
		titleBounds.position.x + titleBounds.size.x / 2.0f,
		titleBounds.position.y + titleBounds.size.y / 2.0f
	});

	titleText.setPosition({
		uiWidth / 2.0f,
		uiHeight / 2.0f
	});
	titleTextShadow.setPosition({
		uiWidth / 2.0f + 10.f,
		uiHeight / 2.0f + 10.f
	});
}

void SplashScreenState::HandleInput(const sf::Event& event)
{ }

void SplashScreenState::Update(sf::Time dt)
{
	elapsedTime += dt;

	if (elapsedTime >= displayDuration)
	{
		context.game.ChangeState(std::make_unique<MenuState>(context));
	}
}

void SplashScreenState::Draw()
{
	context.window.setView(context.uiView);

	context.window.draw(titleTextShadow);
	context.window.draw(titleText);

	context.window.setView(context.window.getDefaultView());
}