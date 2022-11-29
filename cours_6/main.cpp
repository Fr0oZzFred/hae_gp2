using namespace std;
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include "Turtle.hpp"
#include "CmdId.hpp"

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
    reset.id = CmdId::Reset;
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

   


    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Turtle Game");
    sf::Clock t;
    while (window.isOpen()) {
        sf::Time dt = t.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Evaluate Task
        if (turtle.index < (int)turtle.commands.size()) {
            bool taskDone = turtle.evaluate(1);
            turtle.updateHead();
            if(taskDone) turtle.index++;
        }


        window.clear();
        turtle.draw(&window);
        window.display();
    }

    return 0;
};