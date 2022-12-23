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
	return world.collides(offsetX + cx + rx, offsetY + cy + ry);
};