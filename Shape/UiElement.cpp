#include "UiElement.hpp"
#include "Game.hpp"

sf::Vector2f UiElement::getGridPosition() {
	return sf::Vector2f(cx + rx, cy + ry);
}

void UiElement::setPixelPos(sf::Vector2f npos) {
	cx = (int)npos.x / Game::CELL_SIZE;
	cy = (int)npos.y / Game::CELL_SIZE;

	rx = (npos.x - (cx * Game::CELL_SIZE)) / Game::CELL_SIZE;
	ry = (npos.y - (cy * Game::CELL_SIZE)) / Game::CELL_SIZE;

	xx = (int)((cx + rx) * Game::CELL_SIZE);
	yy = (int)((cy + ry) * Game::CELL_SIZE);
};
void UiElement::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Game::CELL_SIZE, npos.y * Game::CELL_SIZE));
};
void UiElement::baseUpdate() {
	updatePos();
	syncPos();
}
void UiElement::updatePos() {
	//Handle rx,ry
	while (rx > 1) {
		rx--;
		cx++;
	}
	while (rx < 0) {
		rx++;
		cx--;
	}
	while (ry > 1) {
		ry--;
		cy++;
	}
	while (ry < 0) {
		ry++;
		cy--;
	}
};

void UiElement::syncPos() {
	xx = (int)((cx + rx) * Game::CELL_SIZE);
	yy = (int)((cy + ry) * Game::CELL_SIZE);
};