#include "Part.hpp"
#include "Lib.hpp"
#include "SFML/System/Vector2.hpp"

void PartController::add(sf::Vector2f pos) {
	data.push_back(Part(pos));
	va.setPrimitiveType(sf::Quads);
}

void PartController::update() {
	for (auto& p : data)
		p.update();
}

void PartController::draw(sf::RenderWindow&win  ) {
	va.clear();
	for (auto& p : data) {
		//p.draw(win);
		p.drawInto(va,win);
	}
	win.draw(va);
}

Part::Part() {
	shp.setOrigin(2, 2);
	shp.setRotation( 360 * Lib::randF());
}

Part::Part(sf::Vector2f pos) : Part() {
	shp.setPosition(pos);
}

void Part::draw(sf::RenderWindow& win) {
	win.draw(shp);
}

void Part::drawInto(sf::VertexArray& va, sf::RenderWindow& win) {
	//auto b = shp.getGlobalBounds();
	//auto left = b.left;
	//auto top = b.top;
	//auto right = b.left + b.width;
	//auto bottom = b.top + b.height;
	auto lb = shp.getLocalBounds();
	auto pos = shp.getPosition();

	auto left = pos.x - lb.width*0.5f;
	auto top = pos.y - lb.height * 0.5f;
	auto right = pos.x + lb.width * 0.5f;
	auto bottom = pos.y + lb.height * 0.5f;

	sf::Vector2f p0(left,top);
	sf::Vector2f p1(right, top);
	sf::Vector2f p2(right, bottom);
	sf::Vector2f p3(left, bottom);

	auto col = shp.getFillColor();
	va.append(sf::Vertex(p0,col));
	va.append(sf::Vertex(p1, col));
	va.append(sf::Vertex(p2, col));
	va.append(sf::Vertex(p3, col));
}


void Part::update(){
	auto pos = shp.getPosition();
	speed.x = speed.x * 0.95 + Lib::randF() * 0.02;
	speed.y += Lib::randF() * 0.1f;
	pos.x += speed.x;
	pos.y += speed.y;
	shp.setPosition(pos);
}
