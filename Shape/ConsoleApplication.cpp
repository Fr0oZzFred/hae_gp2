#include "Lib.hpp"
#include <SFML/Graphics.hpp>
#include "Entities.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "imgui.h"
#include "Player.hpp"

int main(){
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Shape !", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);

	std::vector<sf::Vector2i> sequence;
	int sqcIdx = 0;

	Player player;

	sf::Clock time;
	while (window.isOpen()) {
		sf::Time dt = time.restart();
		sf::Event event;
		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		bool t = true;
		ImGui::SFML::Update(window, dt);
		{
			using namespace ImGui;

			ImGui::Begin("Debug", &t);
			player.im();
			ImGui::End();
		}

		player.update();


		window.clear();
		player.draw(window);
		ImGui::EndFrame();
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}