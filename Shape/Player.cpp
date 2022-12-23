#include "Player.hpp"
#include "imgui.h"
#include "World.hpp"

void Player::im() {
	using namespace ImGui;
	DragFloat2("frict", &frictX, 0.01, 0.5, 1.0);
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", xx);
	Value("pos y", yy);
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
	angle = Lib::lookAt(
		shp->getPosition(), 
		(sf::Vector2f)sf::Mouse::getPosition()
	);
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


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		shoot();
	}


	Entity::baseUpdate();
}
void Player::shoot() {
	world.addEntity(
		new Projectile(
			this,
			(sf::Vector2f)sf::Mouse::getPosition() -
			shp->getPosition()
	));
};