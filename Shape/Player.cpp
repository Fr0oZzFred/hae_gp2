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
};
void Player::update() {
	//Movement
	int x = -sf::Keyboard::isKeyPressed(sf::Keyboard::Left) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Q) +
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) + sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	int y = -sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + -sf::Keyboard::isKeyPressed(sf::Keyboard::Z) +
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) + sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	x = std::clamp(x, -1, 1);
	y = std::clamp(y, -1, 1);
	bool diagonal = false;
	if (x != 0 && y != 0)
		diagonal = true;
	sf::Vector2f dir(x, y);
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		if (diagonal) {
			dx += dir.x * speed * 0.707f;
			dy += dir.y * speed * 0.707f;
		}
		else {
			dx += dir.x * speed;
			dy += dir.y * speed;
		}
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

	Entity::updatePos();

	//Clamp cx,rx,cy,ry
	float resX = 0.0f;
	float resY = 0.0f;

	resX = std::clamp(cx + rx,
		Game::AREA_MARGE_X() / Game::CELL_SIZE + range / Game::CELL_SIZE,
		(Game::WIDTH - Game::AREA_MARGE_X()) / Game::CELL_SIZE - range / Game::CELL_SIZE);
	resY = std::clamp(cy + ry,
		Game::AREA_MARGE_Y() / Game::CELL_SIZE + range / Game::CELL_SIZE,
		(Game::HEIGHT - Game::AREA_MARGE_Y()) / Game::CELL_SIZE - range / Game::CELL_SIZE);
	
	rx = fmod(resX, 1.0f);
	resX -= rx;
	cx = resX;

	ry = fmod(resY, 1.0f);
	resY -= ry;
	cy = resY;


	Entity::syncPos();
}
void Player::shoot() {
	world.addEntity(
		new Projectile(
			this,
			(sf::Vector2f)sf::Mouse::getPosition() -
			shp->getPosition()
	));
};