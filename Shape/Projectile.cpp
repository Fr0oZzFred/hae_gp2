#include "Projectile.hpp"
void Projectile::update() {
	if (world.collides(cx, cy)) {
		shp->setFillColor(sf::Color::Red);

	}
	Entity::update();
}