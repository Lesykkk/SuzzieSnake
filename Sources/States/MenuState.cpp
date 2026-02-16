#include "MenuState.h"

#include "../Game/Game.h"
#include "PlayState.h"
#include "SettingsState.h"

MenuItem::MenuItem(MenuAction act, const sf::Font& font, const std::string& str, unsigned int size)
	: action(act), text(font, str, size)
{ }

MenuState::MenuState(GameContext& context)
	: State(context)
	, titleText(context.mainFont, "MENU", 60)
	, titleTextShadow(context.mainFont, "MENU", 60)
	, itemColor(context.mainColor)
	, itemColorShadow(context.mainColorShadow)
	, itemHoveredColor(context.accentColor)
{
	if (menuSoundBuffer.loadFromFile("assets/sounds/menu.mp3"))
	{
		menuSound.emplace(menuSoundBuffer);
		menuSound->play();
	}
	else
	{
		throw std::runtime_error("Failed to load menu sound!");
	}
	
	const float uiWidth = context.uiView.getSize().x;
	const float uiHeight = context.uiView.getSize().y;

	const float titleY = uiHeight * 0.35f;
	const float shadowOffset = 7.f;
	const float itemsStartY = titleY + 140.f;
	const float itemsSpacing = 80.f;

	titleText.setFillColor(itemColor);
	titleTextShadow.setFillColor(itemColorShadow);

	sf::FloatRect titleBounds = titleText.getLocalBounds();
	titleText.setOrigin({
		titleBounds.position.x + titleBounds.size.x / 2.0f,
		titleBounds.position.y + titleBounds.size.y / 2.0f
		});
	titleText.setPosition({ uiWidth / 2.0f, titleY });

	titleTextShadow.setOrigin({
		titleBounds.position.x + titleBounds.size.x / 2.0f,
		titleBounds.position.y + titleBounds.size.y / 2.0f
		});
	titleTextShadow.setPosition({ uiWidth / 2.0f + shadowOffset, titleY + shadowOffset });

	items.emplace_back(MenuAction::Play, context.mainFont, "PLAY", 44);
	items.emplace_back(MenuAction::Settings, context.mainFont, "SETTINGS", 44);
	items.emplace_back(MenuAction::Exit, context.mainFont, "EXIT", 44);

	for (size_t i = 0; i < items.size(); ++i)
	{
		sf::FloatRect bounds = items[i].text.getLocalBounds();
		items[i].text.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
		items[i].text.setPosition({ uiWidth / 2.0f, itemsStartY + (i * itemsSpacing) });
		items[i].text.setFillColor(itemColor);
	}
}

void MenuState::HandleInput(const sf::Event& event)
{
	auto executeSelected = [&]() {
		switch (items[selectedIndex].action)
		{
		case MenuAction::Play:
			context.game.ChangeState(std::make_unique<PlayState>(context));
			break;
		case MenuAction::Settings:
			context.game.ChangeState(std::make_unique<SettingsState>(context));
			break;
		case MenuAction::Exit:
			context.game.PopState();
			break;
		}
	};

	if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
	{
		sf::Vector2i pixelPos = { mouseMoved->position.x, mouseMoved->position.y };
		sf::Vector2f worldPos = context.window.mapPixelToCoords(pixelPos, context.uiView);

		for (size_t i = 0; i < items.size(); ++i)
		{
			if (items[i].text.getGlobalBounds().contains(worldPos))
			{
				selectedIndex = static_cast<int>(i);
				break;
			}
		}
	}
	else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePressed->button == sf::Mouse::Button::Left)
		{
			sf::Vector2i pixelPos = { mousePressed->position.x, mousePressed->position.y };
			sf::Vector2f worldPos = context.window.mapPixelToCoords(pixelPos, context.uiView);

			for (size_t i = 0; i < items.size(); ++i)
			{
				if (items[i].text.getGlobalBounds().contains(worldPos))
				{
					selectedIndex = static_cast<int>(i);
					menuSound->play();
					executeSelected();
					break;
				}
			}
		}
	}
	else if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::Up || keyEvent->code == sf::Keyboard::Key::W)
		{
			if (selectedIndex > 0)
				selectedIndex--;
			else
				selectedIndex = static_cast<int>(items.size()) - 1;
			menuSound->play();
		}
		else if (keyEvent->code == sf::Keyboard::Key::Down || keyEvent->code == sf::Keyboard::Key::S)
		{
			if (selectedIndex < static_cast<int>(items.size()) - 1)
				selectedIndex++;
			else
				selectedIndex = 0;
			menuSound->play();
		}
		else if (keyEvent->code == sf::Keyboard::Key::Enter)
		{
			menuSound->play();
			executeSelected();
		}
	}
}

void MenuState::Update(sf::Time dt)
{
	for (size_t i = 0; i < items.size(); ++i)
	{
		if (static_cast<int>(i) == selectedIndex)
		{
			items[i].text.setFillColor(itemHoveredColor);
		}
		else
		{
			items[i].text.setFillColor(itemColor);
		}
	}
}

void MenuState::Draw()
{
	context.window.setView(context.uiView);

	context.window.draw(titleTextShadow);
	context.window.draw(titleText);
	for (auto& item : items)
	{
		context.window.draw(item.text);
	}

	context.window.setView(context.window.getDefaultView());
}