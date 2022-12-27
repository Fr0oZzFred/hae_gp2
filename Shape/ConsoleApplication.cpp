#include "Lib.hpp"
#include <SFML/Graphics.hpp>
#include "Entities.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "imgui.h"
#include "Player.hpp"
#include "Bloom.hpp"
#include "HotReloadShader.hpp"
#include "UI.hpp"

static HotReloadShader* bloomShader = nullptr;
static HotReloadShader* blurShader = nullptr;

#pragma region Debug

void debugGrid(sf::VertexArray& grid) {
	for (int x = 0; x < (Game::WIDTH - Game::AREA_MARGE_X() * 2) / Game::CELL_SIZE + 1; x++) {
		for (int y = 0; y < (Game::HEIGHT - Game::AREA_MARGE_Y() * 2) / Game::CELL_SIZE + 1; y++) {
			grid.append(sf::Vertex(sf::Vector2f(x * Game::CELL_SIZE + Game::AREA_MARGE_X(), Game::AREA_MARGE_Y()), sf::Color::White));
			grid.append(sf::Vertex(sf::Vector2f(x * Game::CELL_SIZE + Game::AREA_MARGE_X(), Game::HEIGHT - Game::AREA_MARGE_Y()), sf::Color::White));
			grid.append(sf::Vertex(sf::Vector2f(Game::AREA_MARGE_X(), y * Game::CELL_SIZE + Game::AREA_MARGE_Y()), sf::Color::White));
			grid.append(sf::Vertex(sf::Vector2f(Game::WIDTH - Game::AREA_MARGE_X(), y * Game::CELL_SIZE + Game::AREA_MARGE_Y()), sf::Color::White));
		}
	}
};
#pragma endregion

int main(){
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), Game::NAME, sf::Style::Fullscreen);

	//Bloom
	sf::Texture winTex;
	winTex.create(window.getSize().x, window.getSize().y);

	bloomShader = new HotReloadShader("res/simple.vert", "res/bloom.frag");
	blurShader = new HotReloadShader("res/simple.vert", "res/blur.frag");
	sf::RenderTexture* destX = new sf::RenderTexture();
	destX->create(window.getSize().x, window.getSize().y);
	destX->clear(sf::Color(0, 0, 0, 0));

	sf::RenderTexture* destFinal = new sf::RenderTexture();
	destFinal->create(window.getSize().x, window.getSize().y);
	destFinal->clear(sf::Color(0, 0, 0, 0));

	float bloomWidth = 48;
	sf::Glsl::Vec4 bloomMul(2, 2, 2, 0.8);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);

	std::vector<sf::Vector2i> sequence;
	int sqcIdx = 0;

	Player player;
	world.changeState(GameState::MainMenu);
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
			ImGui::Begin("Player", &t);
			player.im();
			ImGui::End();
			
			ui.im();
		}

		player.update();
		world.update();
		ui.update();


		sf::VertexArray grid(sf::Lines);
		debugGrid(grid);

		window.clear();
		if (world.currentState == GameState::InGame) {
			window.draw(grid);
			player.draw(window);
		}
		world.draw(window);
		ui.draw(window);

		if (bloomWidth)
			Bloom::render(window, winTex, destX, destFinal, &blurShader->sh, &bloomShader->sh, bloomWidth, bloomMul);

		ImGui::EndFrame();
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();


	return 0;
}