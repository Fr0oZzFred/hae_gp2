#include "Player.hpp"
#include "imgui.h"

void Player::im() {
	using namespace ImGui;
	DragFloat2("frict", &frictX, 0.01, 0.5, 1.0);
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);
}
void Player::update() {
	int x = -sf::Keyboard::isKeyPressed(sf::Keyboard::Left) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Q) +
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) + sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	int y = -sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Z) +
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) + sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	x = std::clamp(x, -1, 1);
	y = std::clamp(y, -1, 1);
	sf::Vector2f dir(x, y);
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		dx += dir.x * speed;
		dy += dir.y * speed;
	}
	dx *= frictX;
	dy *= frictY;
	Entity::update();
};