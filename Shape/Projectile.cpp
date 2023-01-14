#include "Projectile.hpp"
void Projectile::update() {
	Entity::baseUpdate();
	if (collides()) {
		switch (type) {
			case 0:
				world.removeEntity(this, world.projectiles);
			break;
			case 1:
				world.addResolution(-1);
				world.removeEntity(this, world.enmProjectiles);
			break;
			case 2:
				world.removeEntity(this, world.enmProjectiles);
			break;

			default:
			break;
		}
		//Spawn particle
		return;
	}
}
bool Projectile::collides() {
	if (world.collidesWithWalls(cx + rx, cy + ry)) {
		if (type == 1) type = 2;
		return true;
	}
	switch (type) {
		case 0:
			if (world.collidesWithEnemies(cx + rx, cy + ry))	return true;
		break;
		case 1:
			if (world.player->isCollided(cx + rx, cy + ry))		return true;
		break;
		default:
		break;
	}
	return false;
}
bool Projectile::isCollided(float gx, float gy) {
	return false;
};