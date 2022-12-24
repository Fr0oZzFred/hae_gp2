#include "UI.hpp"
UI ui;
void UI::add(UiElement* elem) {
	elements.push_back(elem);
}
void UI::update() {
	for (auto& e : elements) e->update();
}
void UI::im() {
	using namespace ImGui;
	bool t = true;
	{
		ImGui::Begin("UI", &t);
		if (ImGui::Button("Save")) save();
		if (ImGui::Button("Load")) load();
		ImGui::End();

		int idx = 0;
		for (auto& e : elements) {
			ImGui::Begin("Truc" + idx, &t);
			e->im();
			ImGui::End();
			idx++;
		}
	}
};
void UI::draw(sf::RenderWindow& window) {
	for (auto& e : elements) e->draw(window);
};
void UI::save() {
	Data::saveUI("res/ui", elements);
};
void UI::load() {
	elements = Data::loadUI("res/ui");
};