using namespace std;
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include "Turtle.hpp"

static float screenX = 1920;
static float screenY = 1080;

sf::Clock t;
int main() {
    sf::Time dt = t.restart();
    Turtle turtle(30, sf::Vector2f(screenX * 0.5f, screenY * 0.5f), 1, sf::Color::Color(0, 102, 0, 255));

    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Turtle Game");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        turtle.update(dt.asSeconds());


        window.clear();
        turtle.draw(&window);
        window.display();
    }

    return 0;
};