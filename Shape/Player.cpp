#include "Player.hpp"
#include "imgui.h"
#include "World.hpp"

void Player::im() {
	using namespace ImGui;
	if (TreeNode("Debug")) {
		DragInt2("cx cy", &cx);
		DragFloat2("rx ry", &rx);
		Value("pos x", xx);
		Value("pos y", yy);
		Value("angle", angle);
		TreePop();
	}
	DragFloat2("Frict", &frictX, 0.01, 0.5, 1.0);
	DragFloat("Speed", &speed, 1.0f, 0.0001f, 100.0f);
	DragFloat("Range", &range, 1.0f, 0.0001f, 1000.0f);
	DragInt("Resolution", &resolution, 1.0f, 3, 100);
	if (ImGui::Button("Save")) save();
	if (ImGui::Button("Load")) load();
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
		dx *= 0.016667; //DeltaTime
		dy *= 0.016667; //DeltaTime
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
	/*Si rotSpeed < 1.0f il faut ?a(angle entre 360 et 0 toujours pas fixed)
	* if (angle < 0.0f) {
	*	angle = 360.0f + angle;
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	*}
	*else {
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	}*/


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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


	//Graphism
	updateShape();

}
void Player::updateShape() {
	auto convexShape = (sf::ConvexShape*)this->shp;
	convexShape->setPointCount(resolution);
	for (int i = 0; i < resolution; i++) {
		double t = (double)i / resolution;
		t *= 3.14159 * 2;
		convexShape->setPoint(i, getAngle(t) * range);
	}
};
void Player::shoot() {
	world.addEntity(
		new Projectile(
			this,
			(sf::Vector2f)sf::Mouse::getPosition() -
			shp->getPosition()
		), world.projectiles
	);
};
void Player::save() {
	Data::savePlayer("res/player.txt");
};
void Player::save(FILE* file) {
	fprintf_s(file, "%f %f %f %f %i \n", frictX, frictY, speed, range, resolution);
}
void Player::load() {
	if(!Data::loadPlayer("res/player.txt")) throw "Player was not able to load correctly";
};
void Player::load(FILE* file) {
	fscanf_s(file, "%f %f %f %f %i \n", &frictX, &frictY, &speed, &range, &resolution);
}

void Player::addResolution(int value) {
	resolution += value;
	if (resolution < 3)
		resolution = 3;
};
