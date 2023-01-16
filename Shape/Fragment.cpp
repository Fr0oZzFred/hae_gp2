#include "Fragment.hpp"

void Fragment::update() {
	time -= 0.016667;
	if (time < 0) {
		world.removeEntity(this, world.fragments);
		return;
	}
	float scale = 1 + (std::cos(world.time->getElapsedTime().asSeconds() * 5.0f) + 1) * 0.5f;
	shp->setScale(sf::Vector2f(scale, scale));
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
