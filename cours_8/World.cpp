#include "Cst.hpp"
#include "World.hpp"

World world;

World::World() {
	staticGfx.setPrimitiveType(sf::Quads);
}

bool World::collides(float gx, float gy) {
	if (gx > Cst::SCREEN_SIZE_X / Cst::CELL_SIZE)
		return true;
	if (gy > ((Cst::SCREEN_SIZE_Y / Cst::CELL_SIZE) - 3))
		return true;
	else if (gx < 0)
		return true;
	else if (gy < 0)
		return true;

	for (auto &w : statics)
		if (gx == w.x && gy == w.y)		return true;

	return false;
}

void World::mkGraphics() {
	sf::Color col = sf::Color::Green;
	staticGfx.clear();
	for (auto iter = statics.begin(); iter != statics.end(); ) {
		sf::Vector2i vtx = *iter;
		staticGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
		staticGfx.append(sf::Vertex(sf::Vector2f((vtx.x + 1) * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
		staticGfx.append(sf::Vertex(sf::Vector2f((vtx.x + 1) * Cst::CELL_SIZE, (vtx.y + 1) * Cst::CELL_SIZE), col));
		staticGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, (vtx.y + 1) * Cst::CELL_SIZE), col));
		iter++;
	}
}

void World::poke(int gx, int gy) {
	for (auto iter = statics.begin(); iter != statics.end(); ) {
		auto& st = *iter;
		if (st.x == gx && st.y == gy) {
			iter = statics.erase(iter);
			mkGraphics();
			return;
		}
		else
			iter++;
	}
	statics.push_back(sf::Vector2i(gx, gy));
	mkGraphics();
}

void World::draw(sf::RenderWindow& win) {
	win.draw(staticGfx);
}