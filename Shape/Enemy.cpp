#include "Enemy.hpp"
void Enemy::im() {
	using namespace ImGui;
	Value("Dist", dist);
};
void Enemy::update() {
	shoot();
	shp->setRotation(Lib::lookAt(shp->getPosition(), world.player->shp->getPosition()));
	if (!moving) return;
	setPixelPos(Lib::lerp(shp->getPosition(), world.player->shp->getPosition(), 0.01f));
	Entity::baseUpdate();
};
void Enemy::shoot() {
	shotTime -= 0.016667;
	if (shotTime > 0) return;

	shotTime = shotRate;
	world.addEntity(
		new Projectile(
			this, world.player->shp->getPosition() - shp->getPosition(),
			sf::Color::Red,
			1), world.enmProjectiles
	);
};
bool Enemy::isCollided(float gx, float gy) {
	sf::Vector2f dist2(gx - (cx + rx), gy - (cy + ry));
	dist = dist2.x * dist2.x + dist2.y * dist2.y;
	dist = sqrt(dist);
	if (range / Game::CELL_SIZE > dist) {
		//Particles
		world.addEntity(new Fragment(sf::Vector2f(xx, yy)), world.fragments);
		world.removeEntity(this, world.enemies);
	}
	return range / Game::CELL_SIZE > dist;
};