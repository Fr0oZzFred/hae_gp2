#include "SoundManager.hpp"

SoundManager soundManager;

void SoundManager::init() {
	if (!mainMenuBuffer.loadFromFile("Ressources/Cybermatic-pulse-_LOOP_.wav"))				throw "Sound not found";
	if (!inGameBuffer.loadFromFile("Ressources/Red-Doors-2.0-_GameClosure-Edition_.wav"))	throw "Sound not found";
	if (!explosion.loadFromFile("Ressources/8bit_bomb_explosion.wav"))						throw "VFX not found";
	if (!shoot.loadFromFile("Ressources/SHOOT011.wav"))										throw "VFX not found";

	mainMenu.setBuffer(mainMenuBuffer);
	mainMenu.setLoop(true);
	mainMenu.setVolume(50);

	inGame.setBuffer(inGameBuffer);
	inGame.setLoop(true);
	inGame.setVolume(65);
};
void SoundManager::playSound() {
	switch (world.currentState) {
		case GameState::Boot:
		break;
		case GameState::MainMenu:
			if (world.oldState == GameState::Credit) return;
			inGame.stop();
			mainMenu.play();
		break;
		case GameState::InGame:
			mainMenu.stop();
			inGame.play();
		break;
		case GameState::Pause:
			inGame.pause();
		break;
		case GameState::GameOver: 
			inGame.stop();
		break;
		default:
		break;
	}
}
void SoundManager::playExplosion() {
	for (auto& s : explosions) {
		if (s->getStatus() == sf::Sound::Status::Stopped) {
			s->play();
			return;
		}
	}
	sf::Sound* nuExplosion = new sf::Sound(explosion);
	nuExplosion->play();
	explosions.push_back(nuExplosion);
};
void SoundManager::playShoot() {
	for (auto& s : shoots) {
		if (s->getStatus() == sf::Sound::Status::Stopped) {
			s->play();
			return;
		}
	}

	sf::Sound * nuShoot = new sf::Sound(shoot);
	nuShoot->play();
	nuShoot->setVolume(15);
	shoots.push_back(nuShoot);
};