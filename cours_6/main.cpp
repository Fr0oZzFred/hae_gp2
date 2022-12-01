using namespace std;
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include "Turtle.hpp"
#include "CmdFile.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

static float screenX = 1920;
static float screenY = 1080;


int main() {

    static Turtle turtle(30, sf::Vector2f(screenX * 0.5f, screenY * 0.5f), 1, sf::Color::Color(0, 102, 0, 255));


    Cmd cmd1;
    cmd1.id = CmdId::moveForward;
    cmd1.data = 100;
    Cmd cmd2;
    cmd2.id = CmdId::rotateRight;
    cmd2.data = 90;
    Cmd cmd3;
    cmd3.id = CmdId::moveForward;
    cmd3.data = 100;
    Cmd cmd4;
    cmd4.id = CmdId::rotateRight;
    cmd4.data = 90;
    Cmd cmd5;
    cmd5.id = CmdId::moveForward;
    cmd5.data = 100;
    Cmd cmd6;
    cmd6.id = CmdId::rotateRight;
    cmd6.data = 90;
    Cmd cmd7;
    cmd7.id = CmdId::moveForward;
    cmd7.data = 100;
    Cmd cmdColorOff;
    cmdColorOff.id = CmdId::draw;
    cmdColorOff.data = 0;
    Cmd cmdColorOn;
    cmdColorOn.id = CmdId::draw;
    cmdColorOn.data = 1;
    Cmd reset;
    reset.id = CmdId::reset;
    reset.data = 0;

    turtle.commands.push_back(cmd1);
    turtle.commands.push_back(cmd2);
    turtle.commands.push_back(cmd3);
    turtle.commands.push_back(cmd4);
    turtle.commands.push_back(cmdColorOff);
    turtle.commands.push_back(cmd5);
    turtle.commands.push_back(cmd6);
    turtle.commands.push_back(cmdColorOn);
    turtle.commands.push_back(cmd7);
    turtle.commands.push_back(reset);

    //CmdFile::save("res/commands.txt", turtle.commands);
    struct stat statut;
    stat("res/commands.txt", &statut);
    auto version = statut.st_mtime;
    turtle.commands = CmdFile::load("res/commands.txt");

    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Turtle Game");
    sf::Clock t;
    float timerVersion = 0;



    ImGui::SFML::Init(window);



    while (window.isOpen()) {
        sf::Time dt = t.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                turtle.index = 0;
                turtle.commands = CmdFile::load("res/commands.txt");
            }
        }

        ImGui::SFML::Update(window, dt);

        ImGui::ShowDemoWindow();

        timerVersion += dt.asSeconds();
        stat("res/commands.txt", &statut);
        auto currentV = statut.st_mtime;

        //Check Timer
        if (timerVersion >= 1) {
            timerVersion--;
            if (version < currentV) {
                turtle.Reset();
                turtle.index = 0;
                turtle.commands = CmdFile::load("res/commands.txt");
                version = currentV;
            }
        }



        //Evaluate Task
        if (turtle.index < (int)turtle.commands.size()) {
            bool taskDone = turtle.evaluate(1);
            turtle.updateHead();
            if(taskDone) turtle.index++;
        }


        window.clear();
        turtle.draw(&window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
};