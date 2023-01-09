#pragma once
#include <vector>
#include "UiElement.hpp"
#include "Button.hpp"
#include "EnemySpawner.hpp"
#include "SpawnEnemy.hpp"

class Data {
public:
	static inline const char* MAIN_PATH = "res/";
	static bool saveUI(const char* path, std::vector<UiElement*>& elements);
	static bool saveEnemySpawner(const char* path, std::vector<SpawnEnemy>& enemies);
	static bool savePlayer(const char* path);
    static std::vector<UiElement*> loadUI(const char* path);
    static std::vector<SpawnEnemy> loadEnemySpawner(const char* path);
	static bool loadPlayer(const char* path);
};