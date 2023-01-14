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
	DragFloat("ShotRate", &shotRate, .05f, 0.0f, 100.0f);
	DragInt("Shot Pattern", &shotPattern, 1.0f, 0, 3);
	DragFloat("Range", &range, 1.0f, 0.0001f, 1000.0f);
	DragInt("Resolution", &resolution, 1.0f, 3, 100);
	if (ImGui::TreeNode("Projectile Color")) {
		ImGui::ColorPicker3("Projectile Color", &projectileColor[0]);
		TreePop();
	}
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
	/*Si rotSpeed < 1.0f il faut ça(angle entre 360 et 0 toujours pas fixed)
	* if (angle < 0.0f) {
	*	angle = 360.0f + angle;
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	*}
	*else {
	*	shp->setRotation(Lib::lerp(shp->getRotation(), angle, rotSpeed));
	}*/

	shoot();

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
	convexShape->setPointCount(resolution);
	for (int i = 0; i < resolution; i++) {
		double t = (double)i / resolution;
		t *= 3.14159 * 2;
		convexShape->setPoint(i, getAngle(t) * range);
	}
};
void Player::shoot() {
	shootTime -= 0.016667;
	if (shootTime > 0.0f) return;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		shootTime = shotRate;
		sf::Vector2f dir = (sf::Vector2f)sf::Mouse::getPosition() - shp->getPosition();
		switch (shotPattern) {
			case 0:
				world.addEntity(
					new Projectile(
						this, dir,
						sf::Color(projectileColor[0] * 255.0f, projectileColor[1] * 255.0f, projectileColor[2] * 255.0f, 255.0f),
						0), world.projectiles
				);
			break;
			case 1:
			for (int i = 0; i < resolution; i++) {
				double t = (double)i / resolution;
				t *= 3.14159 * 2;
				world.addEntity(
					new Projectile(
						this, rotateVec2(getAngle(t), getAngle(shp->getRotation() * ((3.14159f * 2.0f) / 360.0f))),
						sf::Color(projectileColor[0] * 255.0f, projectileColor[1] * 255.0f, projectileColor[2] * 255.0f, 255.0f),
						0), world.projectiles
				);
			}
			break;

			case 2:
			//Front
			world.addEntity(
				new Projectile(
					this, dir,
					sf::Color(projectileColor[0] * 255.0f, projectileColor[1] * 255.0f, projectileColor[2] * 255.0f, 255.0f),
					0), world.projectiles
			);
			//Back
			world.addEntity(
				new Projectile(
					this, -dir,
					sf::Color(projectileColor[0] * 255.0f, projectileColor[1] * 255.0f, projectileColor[2] * 255.0f, 255.0f),
					0), world.projectiles
			);
			break;

			default:
			break;
		}
	}

};
void Player::save() {
	Data::savePlayer("res/player.txt");
};
void Player::save(FILE* file) {
	fprintf_s(file, "%f %f %f %f %f %i %i %f %f %f \n",
		frictX, frictY, speed, range, shotRate, shotPattern, resolution,
		projectileColor[0], projectileColor[1], projectileColor[2]
	);
};
void Player::load() {
	if(!Data::loadPlayer("res/player.txt")) throw "Player was not able to load correctly";
};
void Player::load(FILE* file) {
	fscanf_s(file, "%f %f %f %f %f %i %i %f %f %f \n",
		&frictX, &frictY, &speed, &range, &shotRate, &shotPattern, &resolution,
		&projectileColor[0], &projectileColor[1], &projectileColor[2]
	);
};

void Player::addResolution(int value) {
	resolution += value;
	if (resolution < 3)
		resolution = 3;
}
bool Player::isCollided(float gx, float gy) {
	sf::Vector2f dist2(gx - (cx + rx), gy - (cy + ry));
	float dist = dist2.x * dist2.x + dist2.y * dist2.y;
	dist = sqrt(dist);
	if (range / Game::CELL_SIZE > dist) {
		shp->setFillColor(sf::Color::Magenta);
	}
	else {
		shp->setFillColor(sf::Color::Cyan);
	}
	return range / Game::CELL_SIZE > dist;
};
