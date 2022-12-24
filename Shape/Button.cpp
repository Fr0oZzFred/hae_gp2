#include "Button.hpp"

Button::Button(sf::Vector2f pixelPos) {
	setPixelPos(pixelPos);
	box = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
	box->setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(*box);
};
void Button::update() {
	UiElement::baseUpdate();
	box->setPosition(xx, yy);
}
void Button::im() {
	using namespace ImGui;
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", xx);
	Value("pos y", yy);
};