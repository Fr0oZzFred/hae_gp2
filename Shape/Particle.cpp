#include "Particle.hpp"

void Particle::update() {
	Entity::baseUpdate();
	t += 0.016667 * (2.0f - t) * 2.0f;
	float scale = Lib::lerp(1.0f, maxScale, t);
	shp->setFillColor(Lib::lerp(sf::Color::Red, SFML_ORANGE , t));
	shp->setScale(sf::Vector2f(scale,scale));
	for (int i = 0; i < nb; i++) {
		rec[i].setPosition(rec[i].getPosition() + dir[i] * 2.0f);
		rec[i].rotate(t * Lib::rand());
	}
	if (t > 1.0f) {
		world.removeEntity(this, world.particles);
	}
};

void Particle::draw(sf::RenderWindow &win) {
	win.draw(*shp); 
	for (int i = 0; i < nb; i++)
		win.draw(rec[i]);
};