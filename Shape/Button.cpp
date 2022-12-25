#include "Button.hpp"
#include "UI.hpp"

Button::Button(sf::Vector2f pixelPos) {
	setPixelPos(pixelPos);
	box = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
	box->setFillColor(sf::Color::White);
};
void Button::draw(sf::RenderWindow& window) {
	window.draw(*box);
};
void Button::update() {
	box->setFillColor(sf::Color(r * 255.0f, g * 255.0f, b * 255.0f));
	UiElement::baseUpdate();
	box->setPosition(xx, yy);
};
void Button::im() {
	using namespace ImGui;
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", xx);
	Value("pos y", yy);
	ImGui::ColorPicker3("Color", &r);
	static char _name[64] = "";
	if(ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name), ImGuiInputTextFlags_CharsNoBlank)) return;
	if (ImGui::Button("Rename")) Lib::MemcpyRec(name, _name, 64);
	if (ImGui::Button("Remove")) ui.remove(this);
};
void Button::save(FILE* file) {
	fprintf(file,
		"%s %i %i %f %f %f %f %f \n"
		,name, cx, cy, rx, ry,
		r, g, b
	);
};
void Button::load(FILE* file) {
	static char _name[64] = {};
	fscanf_s(file,
		"%s %i %i %f %f %f %f %f \n",
		_name, 64, &cx, &cy, &rx, &ry,
		&r, &g, &b
	);
	Lib::MemcpyRec(name, _name, 64);
};