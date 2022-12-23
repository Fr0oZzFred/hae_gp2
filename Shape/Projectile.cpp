#include "Projectile.hpp"
void Projectile::update() {
	if (collides()) {
		world.removeEntity(this);
		return;
	}
	Entity::baseUpdate();
}
bool Projectile::collides() {
	float offsetX = dx / Game::CELL_SIZE * 100;
	float offsetY = dy / Game::CELL_SIZE * 100;
	return world.collides( offsetX + cx + rx, offsetY + cy + ry);
};