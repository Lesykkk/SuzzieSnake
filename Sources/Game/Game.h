#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../States/State.h"
#include "Config.h"
#include "GameContext.h"

class Game
{
public:
	static Game& GetInstance();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

	void Run();
	void ApplyConfig();
	void UpdateConfig(const ConfigData& newConfig);
	void PopState();
	void PushState(std::unique_ptr<State> newState);
	void ChangeState(std::unique_ptr<State> newState);
private:
	Game();

	void Init();
	void ApplyStateChanges();
	void HandleInput();
	void Update(sf::Time deltaTime);
	void Render();

	sf::RenderWindow window;
	std::string title = "SUZZIE SNAKE";
	sf::Image windowIcon;
	sf::Color mainColor = { 114, 191, 96 };
	sf::Color mainColorShadow = { 20, 40, 20 };
	sf::Color accentColor = { 255, 255, 120 };
	sf::Font mainFont;
	sf::View uiView;

	ConfigData config;
	ConfigData activeConfig;
	ConfigManager configManager = {"config.ini"};

	enum class StateAction { None, Push, Pop, Change };
	StateAction pendingStateAction = StateAction::None;
	std::unique_ptr<State> pendingState = nullptr;
	std::vector<std::unique_ptr<State>> states;
	GameContext context;
};
