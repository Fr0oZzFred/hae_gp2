#pragma once
#include "World.hpp"
#include <SFML/Audio.hpp>
class SoundManager {
public:
	SoundManager() {};

	sf::SoundBuffer mainMenuBuffer;
	sf::SoundBuffer inGameBuffer;
	sf::SoundBuffer explosion;
	sf::SoundBuffer shoot;
	sf::Sound mainMenu;
	sf::Sound inGame;

	std::vector<sf::Sound*> explosions;
	std::vector<sf::Sound*> shoots;
	void init();
	void playSound();
	void playExplosion();
	void playShoot();
};

extern SoundManager soundManager;