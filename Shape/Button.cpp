#include "Button.hpp"
#include "UI.hpp"

Button::Button(sf::Vector2f pixelPos) {
	setPixelPos(pixelPos);
	box = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
	box->setFillColor(sf::Color::White);
};
void Button::init(const char* _name, sf::Vector2f pixelPos, sf::Vector2f size, sf::Color color) {
};
void Button::draw(sf::RenderWindow& window) {
	window.draw(*box);
};
void Button::update() {
	UiElement::baseUpdate();
	box->setPosition(xx, yy);
};
void Button::im() {
	using namespace ImGui;
	DragInt2("cx cy", &cx);
	DragFloat2("rx ry", &rx);
	Value("pos x", xx);
	Value("pos y", yy);
	static char _name[64] = "";
	if(ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name), ImGuiInputTextFlags_CharsNoBlank)) return;
	if (ImGui::Button("Rename")) Lib::MemcpyRec(name, _name, 64);
	if (ImGui::Button("Remove")) ui.remove(this);
};
void Button::save(FILE* file) {
	fprintf(file, "%s \n", name);
	fprintf(file, "%i %i %f %f \n", cx, cy, rx, ry);
};
void Button::load(FILE* file) {
	static char _name[64] = {};
	fscanf_s(file, "%s \n", _name, 64);
	fscanf_s(file, "%i %i %f %f \n", &cx, &cy, &rx, &ry);
	Lib::MemcpyRec(name, _name, 63);
};