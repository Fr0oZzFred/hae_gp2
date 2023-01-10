#include "Projectile.hpp"
void Projectile::update() {
	if (collides()) {
		world.removeEntity(this, world.projectiles);
		//Spawn particle
		return;
	}
	Entity::baseUpdate();
}
bool Projectile::collides() {
	float offsetX = dx * 2.5f;
	float offsetY = dy * 2.5f;
	if (world.collidesWithWalls(offsetX + cx + rx, offsetY + cy + ry))		return true;
	if (world.collidesWithEnemies(cx + rx, cy + ry))						return true;
	return false;
}
bool Projectile::isCollided(float gx, float gy) {
	return false;
};