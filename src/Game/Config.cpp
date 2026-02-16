#include "Config.h"

#include <algorithm>
#include <fstream>
#include <SFML/Graphics.hpp>

ConfigManager::ConfigManager(const std::string& configPath)
	: configPath(configPath)
{ }

bool ConfigManager::LoadConfig(ConfigData& config)
{
    std::ifstream file(configPath);

    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));

            if (key == "Width") config.width = std::stoi(value);
            else if (key == "Height") config.height = std::stoi(value);
            else if (key == "FramerateLimit") config.framerateLimit = std::stoi(value);
            else if (key == "Fullscreen") config.fullscreen = (value == "1" || value == "true");
            else if (key == "VerticalSync") config.verticalSync = (value == "1" || value == "true");
            else if (key == "Volume") config.volume = std::stof(value);
        }
    }
    return true;
}

bool ConfigManager::SaveConfig(const ConfigData& config) const
{
    std::ofstream file(configPath);
    if (!file.is_open())
        return false;

    file << "[Video]\n"
        << "Width=" << config.width << "\n"
        << "Height=" << config.height << "\n"
        << "Fullscreen=" << config.fullscreen << "\n"
        << "FramerateLimit=" << config.framerateLimit << "\n"
        << "VerticalSync=" << config.verticalSync << "\n"
        << "\n[Audio]\n"
        << "Volume=" << config.volume << "\n";
    return true;
}

void ConfigManager::ValidateConfig(ConfigData& config)
{
    auto modes = sf::VideoMode::getFullscreenModes();
    bool validResolution = false;
    for (auto& res : modes)
    {
        if (res.size.x == config.width && res.size.y == config.height)
        {
            validResolution = true;
            break;
        }
    }
    if (!validResolution)
    {
        auto desktopMode = sf::VideoMode::getDesktopMode();
        config.width = static_cast<unsigned int>(desktopMode.size.x * 0.8f);
        config.height = static_cast<unsigned int>(desktopMode.size.y * 0.8f);
    }
    config.framerateLimit = std::clamp(config.framerateLimit, 30u, 240u);
    config.volume = std::clamp(config.volume, 0.f, 100.f);
}

std::string ConfigManager::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

