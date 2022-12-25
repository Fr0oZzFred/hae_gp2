#include "Button.hpp"
#include "UI.hpp"

void Button::updateColor() {
	sf::Mouse mouse;
	sf::Vector2f mousePos = sf::Vector2f(mouse.getPosition());
	if (collider.contains(mousePos)) {
		if (mouse.isButtonPressed(sf::Mouse::Left)) {
			box->setFillColor(sf::Color(buttonPressed[0] * 255.0f, buttonPressed[1] * 255.0f, buttonPressed[2] * 255.0f));
			return;
		}
		box->setFillColor(sf::Color(buttonSelected[0] * 255.0f, buttonSelected[1] * 255.0f, buttonSelected[2] * 255.0f));
		return;
	}
	box->setFillColor(sf::Color(buttonColor[0] * 255.0f, buttonColor[1] * 255.0f, buttonColor[2] * 255.0f));
};
void Button::draw(sf::RenderWindow& window) {
	window.draw(*box);
	window.draw(text);
};
void Button::update() {
	updateColor();
	text.setFillColor(sf::Color(textColor[0] * 255.0f, textColor[1] * 255.0f, textColor[2] * 255.0f)); 


	//Update Size
	box->setSize(sf::Vector2f(sizeX, sizeY));
	box->setOrigin(box->getSize() * 0.5f);
	text.setOrigin(box->getOrigin());

	//update collider
	collider.top = yy - box->getSize().y * 0.5f;
	collider.left = xx - box->getSize().x * 0.5f;
	collider.width = box->getSize().x;
	collider.height = box->getSize().y;

	text.setCharacterSize(fontSize);


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
		DragFloat2("Size", &sizeX);
		if (ImGui::TreeNode("ButtonColor")) {
			ImGui::ColorPicker3("ButtonColor", &buttonColor[0]);
			TreePop();
		}
		if (ImGui::TreeNode("ButtonSelected")) {
			ImGui::ColorPicker3("ButtonSelected", &buttonSelected[0]);
			TreePop();
		}
		if (ImGui::TreeNode("ButtonPressed")) {
			ImGui::ColorPicker3("ButtonPressed", &buttonPressed[0]);
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
		"%s %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %s %f %f %f\n",
		name, cx, cy, rx, ry,
		buttonColor[0], buttonColor[1], buttonColor[2],
		buttonSelected[0], buttonSelected[1], buttonSelected[2],
		buttonPressed[0], buttonPressed[1], buttonPressed[2],
		sizeX, sizeY,
		offsetX, offsetY, fontSize, content,
		textColor[0], textColor[1], textColor[2]
	);
}
void Button::load(FILE* file) {
	fscanf_s(file,
		"%s %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %s %f %f %f\n",
		_name, 64, &cx, &cy, &rx, &ry,
		&buttonColor[0], &buttonColor[1], &buttonColor[2],
		&buttonSelected[0], &buttonSelected[1], &buttonSelected[2],
		&buttonPressed[0], &buttonPressed[1], &buttonPressed[2],
		&sizeX, &sizeY,
		&offsetX, &offsetY, &fontSize, &content, 128,
		&textColor[0], &textColor[1], &textColor[2]
	);
	Lib::MemcpyRec(name, _name, 64);
	text.setString(content);
};