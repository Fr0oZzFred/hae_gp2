#include "Fragment.hpp"

void Fragment::update() {
	Entity::baseUpdate();
	collider.left = shp->getPosition().x - 5.0f;
	collider.top = shp->getPosition().y - 5.0f;
	collides(world.player);
};
bool Fragment::collides(Entity* player) {
	auto _player = (Player*)player;
	if (player->isCollided(cx + rx, cy + ry)) {
		//Particles
		world.removeEntity(this, world.fragments);
		world.addResolution(1);
		return true;
	}
	return false;
};
