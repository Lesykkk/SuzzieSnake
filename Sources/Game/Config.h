#pragma once

#include <string>

struct ConfigData {
	bool fullscreen	= false;
	bool verticalSync = true;
	unsigned int width = 0;
	unsigned int height	= 0;
	unsigned int framerateLimit = 60;
	float volume = 50.f;
};

class ConfigManager
{
public:
	ConfigManager(const std::string& configPath);

	bool LoadConfig(ConfigData& config);
	bool SaveConfig(const ConfigData& config) const;
	void ValidateConfig(ConfigData& config);
private:
	std::string trim(const std::string& str);

	const std::string configPath;
};

