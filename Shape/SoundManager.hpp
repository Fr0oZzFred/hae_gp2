#pragma once
#include "World.hpp"
#include <SFML/Audio.hpp>
class SoundManager {
public:
	SoundManager() {};

	sf::SoundBuffer mainMenuBuffer;
	sf::Sound mainMenu;
	sf::SoundBuffer inGameBuffer;
	sf::Sound inGame;
	void playSound();
	void init();
};

extern SoundManager soundManager;