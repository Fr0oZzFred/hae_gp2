#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Catmull.hpp"
#include "Line.hpp"
#include "Entities.hpp"
#include "Game.hpp"
#include "Part.hpp"
#include "CmdFile.hpp"
#include "World.hpp"
#include "imgui.h"
#include <unordered_map>
#include <algorithm>
#include "Dijkstra.hpp"


using namespace sf;
class Player : public Entity {
public:
	Player() : Entity( sf::Vector2f(50,100) , new RectangleShape(sf::Vector2f(24,64)) ){
		auto rect  = (sf::RectangleShape*) this->shp;
		rect->setOrigin(12, 64);
		rect->setFillColor(sf::Color::Red);
		rect->setOutlineColor(sf::Color::Green);
		rect->setOutlineThickness(2);
	}
};




static Dijkstra dij;
static Player * player = nullptr;

void printGraph(BaseGraph& g, sf::VertexArray& points) {
	int hcell = Cst::CELL_SIZE >> 1;
	points.clear();
	for (auto& p : g) {
		points.append(sf::Vertex(sf::Vector2f(p.first.x * Cst::CELL_SIZE + hcell, p.first.y * Cst::CELL_SIZE + hcell), sf::Color::Red));
	}
};
void printWayGraph(SpeedingWay& g, sf::VertexArray& points) {
	int hcell = Cst::CELL_SIZE >> 1;
	points.clear();
	for (auto& p : g) {
		points.append(sf::Vertex(sf::Vector2f(p.x * Cst::CELL_SIZE + hcell, p.y * Cst::CELL_SIZE + hcell), sf::Color::Yellow));
	}
};
void printDij(Dijkstra& g, sf::VertexArray& points) {
	int hcell = Cst::CELL_SIZE >> 1;
	points.clear();
	for (auto& p : dij.pred) {
		auto& from = p.first;
		auto& to = p.second;
		points.append(sf::Vertex(sf::Vector2f(from.x * Cst::CELL_SIZE + hcell, from.y * Cst::CELL_SIZE + hcell), sf::Color::Magenta));
		points.append(sf::Vertex(sf::Vector2f(to.x * Cst::CELL_SIZE + hcell, to.y * Cst::CELL_SIZE + hcell), sf::Color::Magenta));
	}
};

void testSFML(){
	player = new Player();
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.0015f;

	ImGui::SFML::Init(window);

	sf::VertexArray points;
	sf::VertexArray way;
	sf::VertexArray ways;
	points.setPrimitiveType(Points);
	way.setPrimitiveType(LinesStrip);
	ways.setPrimitiveType(Lines);

	auto bricks = CmdFile::loadScript("res/save.txt");
	for( auto & c : bricks)
		if (c.id == CmdId::Wall)
			world.statics.push_back(sf::Vector2i(c.x, c.y));
	world.mkGraphics();
	std::cout << "bricks read :" << std::to_string(bricks.size());
	
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			
			ImGui::SFML::ProcessEvent(window, event);
			player->onEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				int mcx = (int)event.mouseButton.x / Cst::CELL_SIZE;
				int mcy = (int)event.mouseButton.y / Cst::CELL_SIZE;
				//add block to world's statics
				//add test against statics in world
				world.poke(mcx, mcy);
				std::vector<Cmd> cmds;
				for(auto &s : world.statics)
					cmds.push_back({ CmdId::Wall,s.x,s.y });
				CmdFile::saveScript("res/save.txt",cmds);
			}

			if (event.type == sf::Event::KeyReleased) {

				if (event.key.code == sf::Keyboard::C) {
					std::unordered_map<sf::Vector2i, bool> g;
					dij.setGraph( g );
				}
				if( event.key.code == sf::Keyboard::G){
					//creer un graph de toute les cases valides

					//std::vector<> g <- contient toutes les cases (cx,cy) valides de notre jeu
					//std::unordered_map<> g <- contient toutes les cases (cx,cy) valides de notre jeu

					// le passer a "quelque chose" qui sera notre futur dijkstra
					//appeler afficher graph( g )
					
					std::unordered_map<sf::Vector2i, bool> g;
					for(int y = 0; y <  1 +Game::HEIGHT / Cst::CELL_SIZE; ++y)
					for(int x = 0; x <  1 +Game::WIDTH / Cst::CELL_SIZE; ++x){
						if( !world.collides(x,y))
							g[sf::Vector2i(x, y)] = true;
					}
					
					printGraph(g,points);

					dij.setGraph(g);
				}

				if (event.key.code == sf::Keyboard::D) {
					std::unordered_map<sf::Vector2i, bool> g;
					for (int y = 0; y < 1 + Game::HEIGHT / Cst::CELL_SIZE; ++y)
						for (int x = 0; x < 1 +Game::WIDTH / Cst::CELL_SIZE; ++x) {
							if (!world.collides(x, y))
								g[sf::Vector2i(x, y)] = true;
						}
					dij.setGraph(g);

					if( false )
					{
						dij.d[sf::Vector2i(1, 3)] = 1000;
						dij.d[sf::Vector2i(1, 0)] = 1;
						VertexList q;
						q.push_back(sf::Vector2i(1, 3));
						q.push_back(sf::Vector2i(1, 0));
						int idx = dij.findMin(q);
						int here = 0; // idx shoudl be 1
					}

					if(false)
					{
						dij.d[sf::Vector2i(1, 0)] = 66;
						dij.updateDist(sf::Vector2i(1, 0), sf::Vector2i(0, 0));
					}

					dij.build(sf::Vector2i(player->cx, player->cy));
					printGraph(g, points);
					printWayGraph(dij.way, way);
					printDij(dij, ways);
				}
			}
		}
		
		player->update();
		bool t = true;
		ImGui::SFML::Update(window, sf::Time( sf::seconds(dt)));
		{
			using namespace ImGui;
			//ImGui::ShowDemoWindow(&t);

			ImGui::Begin("Debug", &t);

			player->im();

			if( TreeNode("dijkstra")){
				dij.im();
				TreePop();
			}

			ImGui::End();
		}
		window.clear();
		
		player->draw(window);
		world.draw(window);
		window.draw(points);
		window.draw(ways);
		window.draw(way);

		ImGui::EndFrame();
		ImGui::SFML::Render(window);
		window.display();
		frameEnd = Lib::getTimestamp();
	}
	ImGui::SFML::Shutdown();
}

int WinMain() {
	testSFML();
	return 0;
}

int main(){
	testSFML();
	return 0;
}