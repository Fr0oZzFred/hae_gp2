#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include "Line.hpp"
static const sf::String projectName = "Eevee";

int testSFML() {
    sf::ContextSettings(0, 0, 2);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), projectName, sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    bool fullscreen = true;

    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Evoli.png")) return EXIT_FAILURE;
    sf::RectangleShape shape(sf::Vector2f(texture.getSize()));
    shape.setTexture(&texture);
    //shape.setFillColor(sf::Color::Magenta);
    int speed = 200;


    sf::RectangleShape line(sf::Vector2f(500, 1));
    line.setPosition(window.getSize().x * .5, window.getSize().y * .5);
    int rotSpeed = 10;


    float t = 0;

    std::vector<sf::RectangleShape> catmullPoints;

    auto plot = [&](sf::Vector2f p) {
        sf::RectangleShape p0(sf::Vector2f(16, 16));
        p0.setOrigin(8, 8);
        p0.setFillColor(sf::Color::White);
        p0.setOutlineColor(sf::Color::Green);
        p0.setOutlineThickness(2);
        p0.setRotation(45);
        p0.setPosition(p);
        catmullPoints.push_back(p0);
    };

    plot(sf::Vector2f(1500, 100));
    plot(sf::Vector2f(50, 500));
    plot(sf::Vector2f(1900, 300));
    plot(sf::Vector2f(1000, 900));

    plot(sf::Vector2f(0, 0));




    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //Handle FullScreen
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                fullscreen ? 
                window.create(sf::VideoMode(1920, 1080), projectName, sf::Style::Default) :
                window.create(sf::VideoMode(1920, 1080), projectName, sf::Style::Fullscreen);
                fullscreen = !fullscreen;
            }
        }

        sf::Vector2f pos = shape.getPosition();
        //Handle Input
        pos.x -= speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Left)     * dt.asSeconds();
        pos.x += speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Right)    * dt.asSeconds();
        pos.y -= speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Up)       * dt.asSeconds();
        pos.y += speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Down)     * dt.asSeconds();

        //Clamp Pos
        int maxX = window.getSize().x - texture.getSize().x;
        int maxY = window.getSize().y - texture.getSize().y;
        if (pos.x < 0)      pos.x = 0;
        if (pos.x > maxX)   pos.x = maxX;
        if (pos.y < 0)      pos.y = 0;
        if (pos.y > maxY)   pos.y = maxY;

        shape.setPosition(pos);

        line.setRotation(line.getRotation() + rotSpeed * dt.asSeconds());

        t -= sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * .01;
        t += sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * .01;
        if (t < 0) t = 0;
        if (t > 1) t = 1;


        catmullPoints[4].setPosition(
            Catmull::polynom2(
                catmullPoints[0].getPosition(),
                catmullPoints[1].getPosition(),
                catmullPoints[2].getPosition(),
                catmullPoints[3].getPosition(),
                t
            ));
        catmullPoints[4].setOutlineColor(sf::Color::Magenta);

        std::vector<sf::Vector2f> points;
        points.push_back(catmullPoints[0].getPosition());
        points.push_back(catmullPoints[1].getPosition());
        points.push_back(catmullPoints[2].getPosition());
        points.push_back(catmullPoints[3].getPosition());


        Line catmullLine;

        catmullLine.setPoints(points, 0.00001);



        window.clear();
        window.draw(shape);
        window.draw(line);
        for(auto p : catmullPoints)
            window.draw(p);
        catmullLine.draw(window);
        window.display();

    }
};

int main() {
    testSFML();
    return 0;
};