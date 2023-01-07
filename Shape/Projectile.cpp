#include "Projectile.hpp"
void Projectile::update() {
	if (collides()) {
		world.removeEntity(this);
		return;
	}
	Entity::baseUpdate();
}
bool Projectile::collides() {
	float offsetX = dx * 2.5f;
	float offsetY = dy * 2.5f;
	if (world.collidesWithWalls(offsetX + cx + rx, offsetY + cy + ry))		return true;
	if (world.collidesWithEnemies(cx + rx, cy + ry))						return true;
}
bool Projectile::isCollided(float gx, float gy) {
	return false;
};