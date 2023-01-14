#include "Background.hpp"

BackGround::BackGround(int startPattern, sf::Clock* _time) {
	pattern = startPattern;
	time = _time;
	for (int i = 0; i < Game::WIDTH; i++)
		background.append(sf::Vertex(sf::Vector2f(i, Game::HEIGHT * 0.5f)));
};
void BackGround::update() {
	shape();
};
float BackGround::getTime() {
	return time->getElapsedTime().asSeconds();
}


void BackGround::Lines() {
	for (int i = 0; i < Game::WIDTH; i++)
		background[i].position = background[i].position + sf::Vector2f(0, std::cos(getTime() + i) * 2.0f);
};


void BackGround::draw(sf::RenderWindow& win) {
	win.draw(background);
};