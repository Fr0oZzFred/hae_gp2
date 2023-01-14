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
	if (ImGui::TreeNode("Shot")) {
		DragInt("Shot Pattern", &shotPattern, 1.0f, 0, 10);
		DragFloat("Shot Rate", &shotRate, .05f, 0.0f, 100.0f);
		if (ImGui::TreeNode("Skills Shot Rate")) {
			DragFloat("Triangle Shot Rate", &triangleShotRate, .05f, 0.0f, 100.0f);
			DragFloat("Square Shot Rate", &squareShotRate, .05f, 0.0f, 100.0f);
			DragFloat("Circle Shot Rate", &circleShotRate, .05f, 0.0f, 100.0f);
			TreePop();
		}
		if (ImGui::TreeNode("Skills Duration")) {
			DragFloat("Triangle Duration", &triangleDuration, .05f, 0.0f, 100.0f);
			DragFloat("Square Duration", &squareDuration, .05f, 0.0f, 100.0f);
			DragFloat("Circle Duration", &circleDuration, .05f, 0.0f, 100.0f);
			TreePop();
		}
		TreePop();
	}
	if (ImGui::TreeNode("Main Color")) {
		ImGui::ColorPicker3("Main Color", &mainColor[0]);
		TreePop();
	}
	if (ImGui::TreeNode("Triangle Color")) {
		ImGui::ColorPicker3("Triangle Color", &triangleColor[0]);
		TreePop();
	}
	if (ImGui::TreeNode("Square Color")) {
		ImGui::ColorPicker3("Square Color", &squareColor[0]);
		TreePop();
	}
	if (ImGui::TreeNode("Circle Color")) {
		ImGui::ColorPicker3("Square Color", &circleColor[0]);
		TreePop();
	}
	if (ImGui::Button("Save")) save();
	if (ImGui::Button("Load")) load();
};
void Player::update() {
	convexShape->setFillColor(sf::Color(currentColor[0] * 255.0f, currentColor[1] * 255.0f, currentColor[2] * 255.0f));

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
	convexShape->setPointCount(displayedResolution);
	for (int i = 0; i < displayedResolution; i++) {
		double t = (double)i / displayedResolution;
		t *= 3.14159 * 2;
		convexShape->setPoint(i, getAngle(t) * range);
	}
};
void Player::shoot() {
	skillTime -= 0.016667;
	if (skillTime < 0.0f)	activateSkill(0);
	shootTime -= 0.016667;
	if (shootTime > 0.0f)	return;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		shootTime = currentShotRate;
		sf::Vector2f dir = (sf::Vector2f)sf::Mouse::getPosition() - shp->getPosition();
		switch (shotPattern) {
			case 0:
				world.addEntity(
					new Projectile(
						this, dir,
						sf::Color(currentColor[0] * 255.0f, currentColor[1] * 255.0f, currentColor[2] * 255.0f),
						0), world.projectiles
				);
			break;

			case 2:
			//Front
			world.addEntity(
				new Projectile(
					this, dir,
					sf::Color(currentColor[0] * 255.0f, currentColor[1] * 255.0f, currentColor[2] * 255.0f),
					0), world.projectiles
			);
			//Back
			world.addEntity(
				new Projectile(
					this, -dir,
					sf::Color(currentColor[0] * 255.0f, currentColor[1] * 255.0f, currentColor[2] * 255.0f),
					0), world.projectiles
			);
			break;

			case 10:
			for (int i = 0; i < displayedResolution; i++) {
				double t = (double)i / displayedResolution;
				t *= 3.14159 * 2;
				world.addEntity(
					new Projectile(
						this, rotateVec2(getAngle(t), getAngle(shp->getRotation() * ((3.14159f * 2.0f) / 360.0f))),
						sf::Color(currentColor[0] * 255.0f, currentColor[1] * 255.0f, currentColor[2] * 255.0f),
						0), world.projectiles
				);
			}
			break;

			default:
			break;
		}
	}

}
void Player::activateSkill(int index) {
	auto triangleButton = (Button*)ui.getText("CompTriangle");
	auto squareButton = (Button*)ui.getText("CompSquare");
	auto circleButton = (Button*)ui.getText("CompCircle");
	bool t = (triangleButton != nullptr);
	bool s = (squareButton != nullptr);
	bool c = (circleButton != nullptr);
	switch (index) {
	case 0:
		currentColor[0] = mainColor[0];
		currentColor[1] = mainColor[1];
		currentColor[2] = mainColor[2];
		world.addResolution(0);
		shotPattern = upgradedPattern;
		currentShotRate = shotRate;
		if(t) triangleButton->usingSkill = false;
		if(s) squareButton->usingSkill = false;
		if(c) circleButton->usingSkill = false;
	break;
	case 1:
		if (shotPattern == 10) return;
		if (resolution <= 3) return;
		currentColor[0] = triangleColor[0];
		currentColor[1] = triangleColor[1];
		currentColor[2] = triangleColor[2];
		skillTime = triangleDuration;
		world.addResolution(-3);
		displayedResolution = 3;
		shotPattern = 10;
		currentShotRate = triangleShotRate;
		if (t) triangleButton->usingSkill = true;
	break;
	case 2:
		if (shotPattern == 10) return;
		if (resolution <= 4) return;
		currentColor[0] = squareColor[0];
		currentColor[1] = squareColor[1];
		currentColor[2] = squareColor[2];
		skillTime = squareDuration;
		world.addResolution(-4);
		displayedResolution = 4;
		shotPattern = 10;
		currentShotRate = squareShotRate;
		if (s) squareButton->usingSkill = true;
	break;
	case 3:
		if (shotPattern == 10) return;
		if (resolution <= 20) return;
		currentColor[0] = circleColor[0];
		currentColor[1] = circleColor[1];
		currentColor[2] = circleColor[2];
		skillTime = circleDuration;
		world.addResolution(-20);
		displayedResolution = 100;
		shotPattern = 10;
		currentShotRate = circleShotRate;
		if (c) circleButton->usingSkill = true;
	break;
	default:
	break;
	}
};
void Player::save() {
	Data::savePlayer("res/player.txt");
};
void Player::save(FILE* file) {
	fprintf_s(file, "%f %f %f %f %f %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f \n",
		frictX, frictY, speed, range, shotRate, shotPattern, resolution,
		mainColor[0], mainColor[1], mainColor[2],
		triangleColor[0], triangleColor[1], triangleColor[2],
		squareColor[0], squareColor[1], squareColor[2],
		circleColor[0], circleColor[1], circleColor[2],
		triangleShotRate, squareShotRate, circleShotRate,
		triangleDuration, squareDuration, circleDuration
	);
};
void Player::load() {
	if(!Data::loadPlayer("res/player.txt")) throw "Player was not able to load correctly";
};
void Player::load(FILE* file) {
	fscanf_s(file, "%f %f %f %f %f %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f \n",
		&frictX, &frictY, &speed, &range, &shotRate, &shotPattern, &resolution,
		&mainColor[0], &mainColor[1], &mainColor[2],
		&triangleColor[0], &triangleColor[1], &triangleColor[2],
		&squareColor[0], &squareColor[1], &squareColor[2],
		&circleColor[0], &circleColor[1], &circleColor[2],
		&triangleShotRate, &squareShotRate, &circleShotRate,
		&triangleDuration, &squareDuration, &circleDuration
	);
};

void Player::addResolution(int value) {
	resolution += value;
	if (resolution < 3) resolution = 3;
	if (skillTime > 0.0f) return;
	displayedResolution = resolution;
}
bool Player::isCollided(float gx, float gy) {
	sf::Vector2f dist2(gx - (cx + rx), gy - (cy + ry));
	float dist = dist2.x * dist2.x + dist2.y * dist2.y;
	dist = sqrt(dist);
	return range / Game::CELL_SIZE > dist;
};
