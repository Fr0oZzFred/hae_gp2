#include "Projectile.hpp"
void Projectile::update() {
	if (world.collides(cx + 1, cy)) {
		world.removeEntity(this);
		return;
	}
	if (world.collides(cx , cy + 1)) {
		world.removeEntity(this);
		return;
	}
	if (world.collides(cx - 1, cy)) {
		world.removeEntity(this);
		return;
	}
	if (world.collides(cx, cy - 1)) {
		world.removeEntity(this);
		return;
	}
	Entity::baseUpdate();
}