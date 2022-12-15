#include "Lib.hpp"
#include <SFML/Graphics.hpp>
#include "Entities.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "imgui.h"
#include "Player.hpp"
#include "Bloom.hpp"
#include "HotReloadShader.hpp"

static HotReloadShader* bloomShader = nullptr;
static HotReloadShader* blurShader = nullptr;


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

		if (bloomWidth)
			Bloom::render(window, winTex, destX, destFinal, &blurShader->sh, &bloomShader->sh, bloomWidth, bloomMul);
		window.display();
	}
	ImGui::SFML::Shutdown();


	return 0;
}