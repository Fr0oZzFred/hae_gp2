#include "Button.hpp"
#include "UI.hpp"

void Button::setText(const char* nuContent) {
	Lib::Memcpy(content, nuContent, 128);
	text.setString(content);
};
void Button::updateColor() {
	sf::Mouse mouse;
	if (!displayButton) return;
	sf::Vector2f mousePos = sf::Vector2f(mouse.getPosition());
	if (collider.contains(mousePos)) {
		if (!pressedPrevFrame && mouse.isButtonPressed(sf::Mouse::Left)) {
			box->setFillColor(sf::Color(buttonPressed[0] * 255.0f, buttonPressed[1] * 255.0f, buttonPressed[2] * 255.0f));
			callPressedFunc();
			return;
		}
		pressedPrevFrame = mouse.isButtonPressed(sf::Mouse::Left);
		box->setFillColor(sf::Color(buttonSelected[0] * 255.0f, buttonSelected[1] * 255.0f, buttonSelected[2] * 255.0f));
		return;
	}
	pressedPrevFrame = mouse.isButtonPressed(sf::Mouse::Left);
	box->setFillColor(sf::Color(buttonColor[0] * 255.0f, buttonColor[1] * 255.0f, buttonColor[2] * 255.0f));
};
void Button::draw(sf::RenderWindow& window) {
	if(displayButton)	window.draw(*box);
	if(displayText)		window.draw(text);
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
}
void Button::callPressedFunc() {
	auto p = (Player*)world.player;
	switch (pressedFunc) {
		case -1:
		break;
		case 0:
			world.changeState(GameState::MainMenu);
		break;
		case 1:
			world.changeState(GameState::InGame);
		break;
		case 2:
			world.quitGame();
		break;
		case 3:
			p->activateSkill(1);
		break;
		case 4:
			p->activateSkill(2);
		break;
		case 5:
			p->activateSkill(3);
		break;
		default:
		throw "Index out of Range";
		break;
	}
};
void Button::im() {
	using namespace ImGui;
	if (ImGui::TreeNode("Main")) {
		ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name), ImGuiInputTextFlags_CharsNoBlank);
		ImGui::Checkbox("Display Button", &displayButton);
		ImGui::Checkbox("Display Text", &displayText);
		if (ImGui::Button("Rename")) Lib::MemcpyRec(name, _name, 64);
		if (ImGui::Button("Remove")) ui.remove(this);
		TreePop();
	}
	if (displayButton && ImGui::TreeNode("Button")) {
		DragInt2("cx cy", &cx);
		DragFloat2("rx ry", &rx);
		Value("pos x", xx);
		Value("pos y", yy);
		DragFloat2("Size", &sizeX);
		ImGui::InputInt("Pressed Func Index", &pressedFunc);
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
	if (displayText && ImGui::TreeNode("Text")) {
		DragFloat2("Offset", &offsetX);
		Value("pos x", xx + offsetX * Game::CELL_SIZE);
		Value("pos y", yy + offsetY * Game::CELL_SIZE);
		DragFloat("Font Size", &fontSize);
		if (ImGui::InputText("Content", content, IM_ARRAYSIZE(content), ImGuiInputTextFlags_CharsNoBlank))
			text.setString(content);
		if (ImGui::TreeNode("TextColor")) {
			ImGui::ColorPicker3("TextColor", &textColor[0]);
			TreePop();
		}
		TreePop();
	}
};
void Button::save(FILE* file) {
	fprintf(file,
		"%s %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %s %f %f %f %i %i %i \n",
		name, cx, cy, rx, ry,
		buttonColor[0], buttonColor[1], buttonColor[2],
		buttonSelected[0], buttonSelected[1], buttonSelected[2],
		buttonPressed[0], buttonPressed[1], buttonPressed[2],
		sizeX, sizeY,
		offsetX, offsetY, fontSize, content,
		textColor[0], textColor[1], textColor[2],
		displayButton, displayText, pressedFunc
	);
}
void Button::load(FILE* file) {
	int buttonBool = -1;
	int textBool = -1;
	fscanf_s(file,
		"%s %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %s %f %f %f %i %i %i \n",
		_name, 64, &cx, &cy, &rx, &ry,
		&buttonColor[0], &buttonColor[1], &buttonColor[2],
		&buttonSelected[0], &buttonSelected[1], &buttonSelected[2],
		&buttonPressed[0], &buttonPressed[1], &buttonPressed[2],
		&sizeX, &sizeY,
		&offsetX, &offsetY, &fontSize, &content, 128,
		&textColor[0], &textColor[1], &textColor[2],
		&buttonBool, &textBool, &pressedFunc
	);
	displayButton = buttonBool;
	displayText = textBool;
	Lib::MemcpyRec(name, _name, 64);
	text.setString(content);
};