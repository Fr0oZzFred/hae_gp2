#include "Projectile.hpp"
void Projectile::update() {
	if (collides()) {
		if (type == 0)
			world.removeEntity(this, world.projectiles);
		else {
			Player* player = (Player*)world.player;
			player->addResolution(-1);
			world.removeEntity(this, world.enmProjectiles);
		}
		//Spawn particle
		return;
	}
	Entity::baseUpdate();
}
bool Projectile::collides() {
	float offsetX = dx * 2.5f;
	float offsetY = dy * 2.5f;
	if (world.collidesWithWalls(offsetX + cx + rx, offsetY + cy + ry))		return true;
	switch (type) {
		case 0:
			if (world.collidesWithEnemies(cx + rx, cy + ry))				return true;
		break;
		case 1:
			if (world.player->collides(cx + rx, cy + ry))					return true;
		break;
		default:
		break;
	}
	return false;
}
bool Projectile::isCollided(float gx, float gy) {
	return false;
};