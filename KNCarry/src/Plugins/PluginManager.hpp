#pragma once

class PluginManager
{
public:
	static bool Initialize();
private:
	static inline bool Initialized = false;
	static bool LoadChampionPlugin();
};

