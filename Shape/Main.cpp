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
#include "Enemy.hpp"
#include "A_etoile.hpp"
#include "EnemySpawner.hpp"
#include <filesystem>
#include "SoundManager.hpp"
#include "Background.hpp"


static HotReloadShader* bloomShader = nullptr;
static HotReloadShader* blurShader = nullptr;


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
void addAreaNodes(std::vector<Node>& area) {
	for (int x = 0; x < (Game::WIDTH - Game::AREA_MARGE_X() * 2) / Game::CELL_SIZE + 1; x++) {
		for (int y = 0; y < (Game::HEIGHT - Game::AREA_MARGE_Y() * 2) / Game::CELL_SIZE + 1; y++) {
			area.push_back(Node{ x,y,0,0 });
		}
	}
};
int main(){
	std::cout << "Current working directory: " << std::filesystem::current_path() << endl;
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), Game::NAME, sf::Style::Fullscreen);
	world.window = &window;

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

	float widthBase = 24;
	float bloomWidth = 24;
	sf::Glsl::Vec4 bloomMul(2, 2, 2, 0.9f);
	float widthSpeed = 5.0f;
	float widthIntensity = 5.0f;

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);
	/*
	* Lag de ouf demander à david
	* 
	A_etoile pathfinding;
	addAreaNodes(pathfinding.area);
	sf::VertexArray path(sf::LinesStrip);
	pathfinding.nearestWay(sf::Vector2i(0, 0), sf::Vector2i(10, 5));
	for (auto n : pathfinding.way) {
		sf::Vertex v(sf::Vector2f(n->x * Game::CELL_SIZE + Game::AREA_MARGE_X(), n->y * Game::CELL_SIZE + Game::AREA_MARGE_Y()), sf::Color::Red);
		v.position += sf::Vector2f(Game::CELL_SIZE * 0.5f, Game::CELL_SIZE * 0.5f);
		path.append(v);
	}
	*/

	soundManager.init();
	enemySpawner.load();
	
	world.player = new Player();
	world.player->load();
	world.changeState(GameState::MainMenu);

	sf::VertexArray grid(sf::Lines);
	debugGrid(grid);

	sf::Clock time;
	world.time = &time;
	BackGround bg(0, &time);


	sf::RectangleShape mask(sf::Vector2f(Game::WIDTH, Game::HEIGHT));
	mask.setFillColor(sf::Color(0, 0, 0, 150.0f));

	sf::Clock dtTime;
	while (window.isOpen()) {
		sf::Time dt = dtTime.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
				world.changeState(GameState::Pause);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
				auto p = (Player*)world.player;
				p->activateSkill(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
				auto p = (Player*)world.player;
				p->activateSkill(2);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
				auto p = (Player*)world.player;
				p->activateSkill(3);
			}
		}
		bool t = true;
		ImGui::SFML::Update(window, dt);
		{
			if (Game::DEBUG) {
				using namespace ImGui;
				ImGui::Begin("Player", &t);
				world.player->im();
				ImGui::End();
				ImGui::Begin("Bloom", &t);
				DragFloat("Width Base", &widthBase);
				DragFloat("Bloom Width", &bloomWidth);
				DragFloat4("Bloom Power", &bloomMul.x, 0.01f);
				DragFloat("Width Speed", &widthSpeed);
				DragFloat("Width Intensity", &widthIntensity);
				ImGui::End();

				enemySpawner.im();
				ui.im();
			}
		}
		world.update();
		ui.update();
		if(world.currentState != GameState::Pause) bg.update();

		bloomWidth = widthBase * 1 + (std::sin(time.getElapsedTime().asSeconds() * widthSpeed ) + 1.0f) * 0.5f * widthIntensity;


		window.clear();
		bg.draw(window);
		if (world.currentState != GameState::MainMenu && world.currentState != GameState::Pause) window.draw(mask);
		if (world.currentState == GameState::InGame || world.currentState == GameState::Pause)	window.draw(grid);
		world.draw(window);
		if (world.currentState == GameState::Pause) window.draw(mask);
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