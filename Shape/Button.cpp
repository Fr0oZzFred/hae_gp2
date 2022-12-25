#include "Button.hpp"
#include "UI.hpp"

void Button::draw(sf::RenderWindow& window) {
	window.draw(*box);
	window.draw(text);
};
void Button::update() {
	box->setFillColor(sf::Color(buttonColor[0] * 255.0f, buttonColor[1] * 255.0f, buttonColor[2] * 255.0f));
	text.setFillColor(sf::Color(textColor[0] * 255.0f, textColor[1] * 255.0f, textColor[2] * 255.0f)); 
	UiElement::baseUpdate();
	box->setPosition(xx, yy);
	text.setPosition(
		xx + offsetX * Game::CELL_SIZE,
		yy + offsetY * Game::CELL_SIZE);
};
void Button::im() {
	using namespace ImGui;
	if (ImGui::TreeNode("Main")) {
		ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name), ImGuiInputTextFlags_CharsNoBlank);
		if (ImGui::Button("Rename")) Lib::MemcpyRec(name, _name, 64);
		if (ImGui::Button("Remove")) ui.remove(this);
		TreePop();
	}
	if (ImGui::TreeNode("Button")) {
		DragInt2("cx cy", &cx);
		DragFloat2("rx ry", &rx);
		Value("pos x", xx);
		Value("pos y", yy);
		if (ImGui::TreeNode("ButtonColor")) {
			ImGui::ColorPicker3("ButtonColor", &buttonColor[0]);
			TreePop();
		}
		TreePop();
	}
	if (ImGui::TreeNode("Text")) {
		DragFloat2("Offset", &offsetX);
		Value("pos x", xx + offsetX * Game::CELL_SIZE);
		Value("pos y", yy + offsetY * Game::CELL_SIZE);
		DragFloat("Font Size", &fontSize);
		if (ImGui::InputText("Content", content, IM_ARRAYSIZE(content), ImGuiInputTextFlags_CharsNoBlank)) {
			text.setString(content);
		}
		if (ImGui::TreeNode("TextColor")) {
			ImGui::ColorPicker3("TextColor", &textColor[0]);
			TreePop();
		}
		TreePop();
	}
};
void Button::save(FILE* file) {
	fprintf(file,
		"%s %i %i %f %f %f %f %f %f %f %f %s %f %f %f\n",
		name, cx, cy, rx, ry,
		buttonColor[0], buttonColor[1], buttonColor[2],
		offsetX, offsetY, fontSize, content,
		textColor[0], textColor[1], textColor[2]
	);
};
void Button::load(FILE* file) {
	fscanf_s(file,
		"%s %i %i %f %f %f %f %f %f %f %f %s %f %f %f\n",
		_name, 64, &cx, &cy, &rx, &ry,
		&buttonColor[0], &buttonColor[1], &buttonColor[2],
		&offsetX, &offsetY, &fontSize, &content, 128,
		&textColor[0], &textColor[1], &textColor[2]
	);
	Lib::MemcpyRec(name, _name, 64);
	text.setString(content);
};