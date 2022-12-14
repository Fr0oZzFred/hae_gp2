#include "EnemySpawner.hpp"

EnemySpawner enemySpawner;

EnemySpawner::EnemySpawner() {}
void EnemySpawner::Spawn(SpawnEnemy enm) {
	Spawn((Side)enm.side, enm.lerpPos);
};
void EnemySpawner::Spawn(Side side, float lerpPos) {
	world.addEntity(new Enemy(SideToAreaPos(side, lerpPos)), world.enemies);
};
sf::Vector2f EnemySpawner::SideToAreaPos(Side side, float lerpPos) {
	switch (side) {
		case Side::Top:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					lerpPos);
		case Side::Right:
			return Lib::lerp(sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),	sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		case Side::Bot:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		case Side::Left:
			return Lib::lerp(sf::Vector2f(Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()),					sf::Vector2f(Game::AREA_MARGE_X(),				 Game::HEIGHT - Game::AREA_MARGE_Y()),	lerpPos);
		default:
			return sf::Vector2f(0, 0);
	}
}
void EnemySpawner::checkSpawn() {
	if (idx >= enemies.size()) {
		stop();
		return;
	}
	while (enemies[idx].time < time.getElapsedTime().asSeconds()) {
		Spawn(enemies[idx++]);
		if (idx >= enemies.size()) {
			stop();
			return;
		}
	}
};
void EnemySpawner::restart() {
	enemySpawner.time.restart();
	idx = 0;
	enabled = true;
};
void EnemySpawner::stop() {
	idx = 0;
	enabled = false;
};
void EnemySpawner::update() {
	if (!enabled) return;

	checkSpawn();
};
void EnemySpawner::im() {
	using namespace ImGui;
	bool t = true;
	ImGui::Begin("EnemySpawner", &t);
	Value("Time", enemySpawner.time.getElapsedTime().asSeconds());

	if (TreeNode("Show Enemies list")) {
		int i = 0;
		for (auto &e : enemies) {
			std::string name = "Enemy " + std::to_string(i);
			if (TreeNode(name.c_str())) {
				e.im();
				if (ImGui::Button("Remove"))	remove(i);
				TreePop();
			}
			i++;
		}
		TreePop();
	}

	if (TreeNode("New Enemy")) {
		enemy.im();
		if (ImGui::Button("Add"))	add();
		TreePop();
	}

	if (ImGui::Button("Sort"))		sort();
	if (ImGui::Button("Save"))		save();
	if (ImGui::Button("Load"))		load();
	if (ImGui::Button("Restart"))	restart();
	ImGui::End();
};
void EnemySpawner::save() {
	sort();
	Data::saveEnemySpawner("res/enemies.txt", enemies);
};
void EnemySpawner::load() {
	enemies = Data::loadEnemySpawner("res/enemies.txt");
};
void EnemySpawner::load(const char* path) {
	enemies = Data::loadEnemySpawner(path);
};
void EnemySpawner::add() {
	enemies.push_back(enemy);
	sort();
};
void EnemySpawner::remove(int idx) {
	int i = 0;
	for (auto iter = enemies.begin(); iter != enemies.end();) {
		if (i++ == idx) {
			iter = enemies.erase(iter);
			return;
		}
		else
			iter++;
	}
}
void EnemySpawner::sort() {
	std::sort(enemies.begin(), enemies.end());
};