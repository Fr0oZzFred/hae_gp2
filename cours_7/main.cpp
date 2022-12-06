using namespace std;
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

static float screenX = 1920;
static float screenY = 1080;


int main() {

    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Turtle Game");
    sf::Clock t;


    ImGui::SFML::Init(window);


    while (window.isOpen()) {
        sf::Time dt = t.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, dt);

        ImGui::ShowDemoWindow();


        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
};