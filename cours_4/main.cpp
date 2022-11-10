#include <iostream>
#include "Lib.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window");
    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Evoli.png")) return EXIT_FAILURE;
    sf::RectangleShape shape(sf::Vector2f(texture.getSize()));
    shape.setTexture(&texture);
    //shape.setFillColor(sf::Color::Magenta);
    int speed = 10;

    std::cout << window.getSize().x;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f pos = shape.getPosition();
        //Handle Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))     pos.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    pos.x += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))     pos.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))       pos.y -= speed;

        //Clamp Pos
        int maxX = window.getSize().x - texture.getSize().x;
        int maxY = window.getSize().y - texture.getSize().y;
        if (pos.x < 0)                      pos.x = 0;
        if (pos.x > maxX)                   pos.x = maxX;
        if (pos.y < 0)                      pos.y = 0;
        if (pos.y > maxY)                   pos.y = maxY;

        shape.setPosition(pos);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};