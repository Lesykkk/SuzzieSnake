#include "Game.h"

#include <SFML/Audio.hpp>
#include "../States/SplashScreenState.h"

Game::Game()
	: context(*this, window, config, configManager, uiView, mainFont, title, mainColor, mainColorShadow, accentColor)
{   
    Init();
}

void Game::Init()
{
    configManager.LoadConfig(config);
    configManager.ValidateConfig(config);
    configManager.SaveConfig(config);

    if (!mainFont.openFromFile("assets/fonts/PressStart2P-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load main font");
    }

    if (!windowIcon.loadFromFile("assets/textures/snake.png"))
    {
        throw std::runtime_error("Failed to load window icon");
    }

    uiView.setSize({ 1920.f, 1080.f });
    uiView.setCenter({ 1920.f / 2.f, 1080.f / 2.f });
    
    ApplyConfig();

    ChangeState(std::make_unique<SplashScreenState>(context));
}

void Game::ApplyConfig()
{
    bool fullscreenChanged = (activeConfig.fullscreen != config.fullscreen);
    bool resolutionChanged = (activeConfig.width != config.width) || (activeConfig.height != config.height);

    bool needsRecreate = !window.isOpen() || fullscreenChanged || (config.fullscreen && resolutionChanged);
    bool needsResize = !needsRecreate && resolutionChanged;
    
    if (needsRecreate)
    {
        window.create(
            sf::VideoMode({ config.width, config.height }),
            "Suzzie Snake",
            sf::Style::Close,
            config.fullscreen ? sf::State::Fullscreen : sf::State::Windowed
        );
        if (windowIcon.getSize().x > 0)
        {
            window.setIcon(windowIcon);
        }
    }
    else if (needsResize)
    {
        window.setSize({ config.width, config.height });
        window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(config.width), static_cast<float>(config.height) })));
    }

    if (!config.fullscreen && (needsRecreate || needsResize))
    {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        int posX = static_cast<int>((desktop.size.x - config.width) / 2);
        int posY = static_cast<int>((desktop.size.y - config.height) / 2);

        window.setPosition({ posX, posY });
    }

    float windowWidth = static_cast<float>(config.width);
    float windowHeight = static_cast<float>(config.height);

    float viewRatio = uiView.getSize().x / uiView.getSize().y;
    float windowRatio = windowWidth / windowHeight;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if (windowRatio < viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    }
    else {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }
    uiView.setViewport(sf::FloatRect({ posX, posY }, { sizeX, sizeY }));

    if (config.verticalSync)
    {
        window.setFramerateLimit(0);
        window.setVerticalSyncEnabled(true);
    }
    else
    {
        window.setVerticalSyncEnabled(false);
        window.setFramerateLimit(config.framerateLimit);
    }

	sf::Listener::setGlobalVolume(config.volume);

    activeConfig = config;
}
void Game::UpdateConfig(const ConfigData& newConfig)
{
    config = newConfig;
    configManager.ValidateConfig(config);
    configManager.SaveConfig(config);
    ApplyConfig();
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

    while (window.isOpen())
    {
        ApplyStateChanges();
        if (states.empty())
            break;

        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

		HandleInput();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            Update(timePerFrame);
        }
        Render();
    }
}

void Game::PushState(std::unique_ptr<State> newState)
{
	pendingState = std::move(newState);
	pendingStateAction = StateAction::Push;
}
void Game::PopState()
{
	pendingStateAction = StateAction::Pop;
}
void Game::ChangeState(std::unique_ptr<State> newState)
{
    pendingState = std::move(newState);
    pendingStateAction = StateAction::Change;
}
void Game::ApplyStateChanges()
{
    if (pendingStateAction == StateAction::Push && pendingState)
    {
        states.push_back(std::move(pendingState));
    }
    else if (pendingStateAction == StateAction::Pop && !states.empty())
    {
        states.pop_back();
    }
    else if (pendingStateAction == StateAction::Change && pendingState)
    {
        while (!states.empty())
        {
			states.pop_back();
        }
		states.push_back(std::move(pendingState));
    }
	pendingStateAction = StateAction::None;
	pendingState = nullptr;
}

void Game::HandleInput()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        
        if (!states.empty())
        {
            states.back()->HandleInput(*event);
        }
	}
}
void Game::Update(sf::Time deltaTime)
{
    if (!states.empty())
    {
        states.back()->Update(deltaTime);
    }
}
void Game::Render()
{
    window.clear(sf::Color::Black);
    for (auto& state : states)
    {
        state->Draw();
    }
    window.display();
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}