#include "SoundManager.hpp"

SoundManager soundManager;

void SoundManager::playSound() {
	switch (world.currentState) {
		case GameState::Boot:
		break;
		case GameState::MainMenu:
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
};
void SoundManager::init() {
	if (!mainMenuBuffer.loadFromFile("Ressources/Cybermatic-pulse-_LOOP_.wav"))				throw "Sound not found";
	if (!inGameBuffer.loadFromFile("Ressources/Red-Doors-2.0-_GameClosure-Edition_.wav"))	throw "Sound not found";

	mainMenu.setBuffer(mainMenuBuffer);
	mainMenu.setLoop(true);

	inGame.setBuffer(inGameBuffer);
	inGame.setLoop(true);
};