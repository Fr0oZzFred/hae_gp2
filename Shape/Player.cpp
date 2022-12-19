#include "Player.hpp"
#include "imgui.h"

void Player::im() {
	using namespace ImGui;
	DragFloat2("frict", &frictX, 0.01, 0.5, 1.0);
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);
	Value("dir x", mouseDir.x);
	Value("dir y", mouseDir.y);
	Value("angle", angle);
}
void Player::update() {
	//Movement
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


	//Rotation
	mouseDir = (sf::Vector2f)sf::Mouse::getPosition() - shp->getPosition();
	Lib::safeNormalize(mouseDir);
	angle = std::atan2(mouseDir.y, mouseDir.x);
	angle *= 180.f / 3.14159;
	float rotSpeed = 1.0f;
	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	/*Si rotSpeed < 1.0f il faut ça(angle entre 360 et 0 toujours pas fixed)
	* if (angle < 0.0f) {
	*	angle = 360.0f + angle;
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	*}
	*else {
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	}*/

	


	Entity::update();
};