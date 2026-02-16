#include "SettingsState.h"

#include "MenuState.h"
#include "../Game/Game.h"
#include <algorithm>

SettingsState::SettingsState(GameContext& context)
	: State(context)
	, titleText(context.mainFont)
	, hintText(context.mainFont)
	, localConfig(context.config)
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

	float currentY = uiHeight * 0.15f;
	const float spacingY = 60.f;
	const float categorySpacingY = 40.f;
	const float headerIndentX = uiWidth * 0.5f - 220.f;
	const float itemIndentX = headerIndentX + 60.f;

	// ==== SETTINGS ====
	titleText.setString("SETTINGS");
	titleText.setCharacterSize(44);
	titleText.setFillColor(context.mainColor);
	auto titleBounds = titleText.getLocalBounds();
	titleText.setOrigin({ titleBounds.size.x / 2.f, titleBounds.size.y / 2.f });
	titleText.setPosition({ uiWidth / 2.f, currentY });
	currentY += 100.f;
	auto addHeader = [&](const std::string& title) {
		categoryHeaders.emplace_back(context.mainFont);
		categoryHeaders.back().setString(title);
		categoryHeaders.back().setCharacterSize(28);
		categoryHeaders.back().setFillColor(context.mainColor);
		categoryHeaders.back().setPosition({ headerIndentX, currentY });
		currentY += spacingY;
	};

	// ==== VIDEO ====
	addHeader("Video:");
	videoModes = sf::VideoMode::getFullscreenModes();
	if (videoModes.empty()) return;
	currentModeIndex = 0;
	for (size_t i = 0; i < videoModes.size(); ++i)
	{
		if (videoModes[i].size.x == context.config.width && videoModes[i].size.y == context.config.height)
		{
			currentModeIndex = static_cast<int>(i);
			break;
		}
	}
	AddItem(itemIndentX, currentY,
		[&]() { if (currentModeIndex > 0) currentModeIndex--; localConfig.width = videoModes[currentModeIndex].size.x; localConfig.height = videoModes[currentModeIndex].size.y; },
		[&]() { if (currentModeIndex < static_cast<int>(videoModes.size()) - 1) currentModeIndex++; localConfig.width = videoModes[currentModeIndex].size.x; localConfig.height = videoModes[currentModeIndex].size.y; },
		[&]() { return "Resolution < " + std::to_string(localConfig.width) + "x" + std::to_string(localConfig.height) + " >"; }
	);
	currentY += spacingY;
	AddItem(itemIndentX, currentY,
		[&]() { localConfig.fullscreen = !localConfig.fullscreen; },
		[&]() { localConfig.fullscreen = !localConfig.fullscreen; },
		[&]() { return std::string("Fullscreen < ") + (localConfig.fullscreen ? "On" : "Off") + " >"; }
	);
	currentY += spacingY;
	AddItem(itemIndentX, currentY,
		[&]() { localConfig.verticalSync = !localConfig.verticalSync; },
		[&]() { localConfig.verticalSync = !localConfig.verticalSync; },
		[&]() { return std::string("VSync      < ") + (localConfig.verticalSync ? "On" : "Off") + " >"; }
	);
	currentY += spacingY;
	AddItem(itemIndentX, currentY,
		[&]() { localConfig.framerateLimit = std::max(30u, localConfig.framerateLimit - 30u); },
		[&]() { localConfig.framerateLimit = std::min(240u, localConfig.framerateLimit + 30u); },
		[&]() { return "Max FPS    < " + std::to_string(localConfig.framerateLimit) + " >"; }
	);
	currentY += spacingY + categorySpacingY;

	// ==== AUDIO ====
	addHeader("Audio:");
	AddItem(itemIndentX, currentY,
		[&]() { localConfig.volume = std::max(0.f, localConfig.volume - 10.f); },
		[&]() { localConfig.volume = std::min(100.f, localConfig.volume + 10.f); },
		[&]() { return "Volume     < " + std::to_string(static_cast<int>(localConfig.volume)) + "% >"; }
	);

	hintText.setString("Press ESC to save and go back");
	hintText.setCharacterSize(18);
	hintText.setFillColor(context.mainColor);
	auto hintBounds = hintText.getLocalBounds();
	hintText.setOrigin({ hintBounds.size.x / 2.f, hintBounds.size.y / 2.f });
	hintText.setPosition({ uiWidth / 2.f, uiHeight - 60.f });


	UpdateTexts();
	UpdateSelection();
}

void SettingsState::AddItem(float x, float y, std::function<void()> onLeft, std::function<void()> onRight, std::function<std::string()> getText)
{
	items.push_back({ sf::Text(context.mainFont), onLeft, onRight, getText });
	auto& itemText = items.back().text;
	itemText.setCharacterSize(24);
	itemText.setPosition({ x, y });
}

void SettingsState::HandleInput(const sf::Event& event)
{
	if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::Escape || keyEvent->code == sf::Keyboard::Key::Backspace)
		{
			context.game.UpdateConfig(localConfig);
			context.game.ChangeState(std::make_unique<MenuState>(context));
		}
		else if (keyEvent->code == sf::Keyboard::Key::Up || keyEvent->code == sf::Keyboard::Key::W)
		{
			if (selectedIndex > 0) selectedIndex--;
			UpdateSelection();
			menuSound->play();
		}
		else if (keyEvent->code == sf::Keyboard::Key::Down || keyEvent->code == sf::Keyboard::Key::S)
		{
			if (selectedIndex < static_cast<int>(items.size()) - 1) selectedIndex++;
			UpdateSelection();
			menuSound->play();
		}
		else if (keyEvent->code == sf::Keyboard::Key::Left || keyEvent->code == sf::Keyboard::Key::A)
		{
			items[selectedIndex].onLeft();
			UpdateTexts();
			menuSound->play();
		}
		else if (keyEvent->code == sf::Keyboard::Key::Right || keyEvent->code == sf::Keyboard::Key::D)
		{
			items[selectedIndex].onRight();
			UpdateTexts();
			menuSound->play();
		}
	}
}

void SettingsState::Update(sf::Time dt)
{
}

void SettingsState::Draw()
{
	context.window.setView(context.uiView);

	context.window.draw(titleText);
	for (const auto& header : categoryHeaders) context.window.draw(header);
	for (const auto& item : items) context.window.draw(item.text);
	context.window.draw(hintText);

	context.window.setView(context.window.getDefaultView());
}

void SettingsState::UpdateSelection()
{
	for (size_t i = 0; i < items.size(); ++i)
	{
		items[i].text.setFillColor(i == selectedIndex ? context.accentColor : context.mainColor);
	}
}

void SettingsState::UpdateTexts()
{
	for (auto& item : items)
	{
		item.text.setString(item.getText());
	}
}