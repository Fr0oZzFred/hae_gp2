#include "Fragment.hpp"

void Fragment::update() {
	Entity::baseUpdate();
	collider.left = shp->getPosition().x - 5.0f;
	collider.top = shp->getPosition().y - 5.0f;
	collides(world.player);
}
bool Fragment::collides(Entity* player) {
	auto _player = (Player*)player;
	sf::Vector2f dist2(
		(_player->cx + _player->rx) - (cx + rx),
		(_player->cy + _player->ry) - (cy + ry)
	);
	float dist = dist2.x * dist2.x + dist2.y * dist2.y;
	dist = sqrt(dist);
	if (_player->range / Game::CELL_SIZE > dist) {
		//Particles
		world.removeEntity(this, world.fragments);
		_player->addResolution(1);
	}
	return _player->range / Game::CELL_SIZE > dist;
}
