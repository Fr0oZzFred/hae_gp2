#include "Game.hpp"

const sf::String Game::NAME = "Shape !";
const float Game::WIDTH = 1920;
const float Game::HEIGHT = 1080;

float Game::AREA_X_SIDE() {
	return (WIDTH - HEIGHT) * 0.5f;
};
float Game::AREA_Y_SIDE() {
	return CELL_SIZE * 0.5f;
};

