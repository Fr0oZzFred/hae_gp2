#include "Enemy.hpp"
void Enemy::im() {
	using namespace ImGui;
	Value("Dist", dist);
};
void Enemy::update() { 
	if (dead) return;
	shp->setRotation(Lib::lookAt(shp->getPosition(), player->shp->getPosition()));
	setPixelPos(Lib::lerp(shp->getPosition(), player->shp->getPosition(), 0.01f));
	Entity::baseUpdate();
};
void Enemy::shoot() {
}
bool Enemy::isCollided(float gx, float gy) {
	sf::Vector2f dist2(gx - (cx + rx), gy - (cy + ry));
	dist = dist2.x * dist2.x + dist2.y * dist2.y;
	dist = sqrt(dist);
	if (range / Game::CELL_SIZE > dist) { 
		dead = true;
		shp->setFillColor(sf::Color::Magenta);
	}
	return range / Game::CELL_SIZE > dist;
};