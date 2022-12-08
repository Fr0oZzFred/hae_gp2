using namespace std;
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Entity.hpp"
#include "Cst.hpp"
#include "World.hpp"

static float screenX = 1920;
static float screenY = 1080;


int main() {

    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Grid");
    sf::Clock t;

    vector<Entity> entities;

    ImGui::SFML::Init(window);
    Entity cube(new sf::RectangleShape(sf::Vector2f(16,16)),
        sf::Vector2f(Cst::SCREEN_SIZE_X * 0.4f,Cst::SCREEN_SIZE_Y * 0.4f),
        &entities);

    while (window.isOpen()) {
        sf::Time dt = t.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                int mcx = (int)event.mouseButton.x / Cst::CELL_SIZE;
                int mcy = (int)event.mouseButton.y / Cst::CELL_SIZE;
                //add block to world's statics
                //add test against statics in world
                world.poke(mcx, mcy);
            }
        }

        ImGui::SFML::Update(window, dt);
        //ImGui::ShowDemoWindow();
        float sp = 0.2f;
        int x = -sf::Keyboard::isKeyPressed(sf::Keyboard::Left) +
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        int y = -sf::Keyboard::isKeyPressed(sf::Keyboard::Up) +
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        sf::Vector2f dir(x,y);
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len) {
            cube.dx += dir.x * sp;
            cube.dy += dir.y * sp;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            cube.jump();
        }

        cube.update();

        bool b = true;
        ImGui::Begin("debug", &b);
        cube.im();
        ImGui::End();

        window.clear();

        world.draw(window);
        ImGui::SFML::Render(window);
        cube.draw(&window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
};