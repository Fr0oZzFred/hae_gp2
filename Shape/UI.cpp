#include "UI.hpp"

UI ui;
void UI::add(UiElement* elem) {
	elements.push_back(elem);
};
void UI::remove(UiElement* elem) {
	for (auto iter = elements.begin(); iter != elements.end();) {
		if (*iter == elem) {
			iter = elements.erase(iter);
			delete elem;
			return;
		}
		else
			iter++;
	}
}
UiElement* UI::getText(const char* buttonName) {
	for (auto& e : elements)
		if (Lib::StrCmp(e->name, buttonName) == 0) return e;
	return nullptr;
};
void UI::update() {
	for (auto& e : elements) {
		e->update();
		if (elementsChanged) {
			elementsChanged = false;
			return;
		}
	}
};
void UI::im() {
	bool t = true;
	bool showElementsIm = false;
	{
		ImGui::Begin("UI", &t);
		if (showElementsIm = ImGui::TreeNode("Elements")) {
			for (auto& e : elements) {
				ImGui::Text(e->name);
			}
			ImGui::TreePop();
		}


		if (ImGui::Button("New Button")) add(new Button());


		if (ImGui::Button("Save")) save();
		if (ImGui::Button("Load")) load();
		ImGui::End();


		if (!showElementsIm) return;
		
		for (auto e : elements) {
			ImGui::Begin(e->name, &t);
			e->im();
			ImGui::End();
		}
	}
};
void UI::draw(sf::RenderWindow& window) {
	for (auto& e : elements) e->draw(window);
};
void UI::save() {
	Data::saveUI("res/ui.txt", elements);
};
void UI::load() {
	elements = Data::loadUI("res/ui.txt");
}
void UI::load(const char* path) {
	elements = Data::loadUI(path);
	elementsChanged = true;
};