#include "Game.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>
const int Game::WIDTH = 1600;
const int Game::HEIGHT = 900;

static std::vector<sf::Sound*> snd;
static std::unordered_map<std::string, sf::SoundBuffer*> sndBufs;

void Game::playSound(const char * snd) {
	sf::SoundBuffer* sb = sndBufs[snd];
	if (!sb) {
		sb = new sf::SoundBuffer();
		sb->loadFromFile(snd);
		sndBufs[snd] = sb;
	}

	auto s = new sf::Sound(*sb);
	s->play();
	::snd.push_back(s);
}

void Game::playExplosion() {
	playSound("res/Explosion.wav");
}

void Game::playImpact() {
	playSound("res/Bump.wav");
}

void Game::garbage() {

}

