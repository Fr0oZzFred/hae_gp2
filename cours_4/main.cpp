#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    shape.setPosition(
        0,
        window.getSize().y - texture.getSize().y
    );
    sf::Texture textureSoleil;
    if (!textureSoleil.loadFromFile("Assets/full.png")) return EXIT_FAILURE;
    sf::RectangleShape shapeSoleil(sf::Vector2f(texture.getSize()) * .5f);
    shapeSoleil.setScale(sf::Vector2f(1, 0.5f));
    shapeSoleil.setTexture(&textureSoleil);
    shapeSoleil.setPosition(
        window.getSize().x - texture.getSize().x * .5f,
        0
    );
    //shape.setFillColor(sf::Color::Magenta);
    int speed = 200;
    sf::SoundBuffer shootSoundBuff;
    if(!shootSoundBuff.loadFromFile("Assets/Lancer-Splat-Sound-Effect-_Deltarune_.wav")) return EXIT_FAILURE;
    sf::Sound shootSound(shootSoundBuff);

    sf::RectangleShape line(sf::Vector2f(200, 10));
    line.setPosition(window.getSize().x * .5, window.getSize().y *0.75f );
    int rotSpeed = 20;


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



    std::vector<sf::CircleShape> balls;
    std::vector<float> ballsT;

    bool isShooting = false;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        isShooting = false;
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

            //
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                float size = 10;
                sf::CircleShape shoot(size);
                shoot.setOrigin(size *.5f, size *.5f);
                shoot.setPosition(line.getPosition());
                shoot.setFillColor(sf::Color::Red);
                balls.push_back(shoot);
                ballsT.push_back(0);
                isShooting = true;
                shootSound.play();
            }
        }

        sf::Vector2f pos = line.getPosition();
        //Handle move
        pos.x -= speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * dt.asSeconds();
        pos.x += speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * dt.asSeconds();
        //pos.y -= speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Up)       * dt.asSeconds();
        //pos.y += speed * sf::Keyboard::isKeyPressed(sf::Keyboard::Down)     * dt.asSeconds();

        //Clamp Pos
        int maxX = window.getSize().x;
        //int maxY = window.getSize().y - texture.getSize().y;
        if (pos.x < 0)      pos.x = 0;
        if (pos.x > maxX)   pos.x = maxX;
        //if (pos.y < 0)      pos.y = 0;
        //if (pos.y > maxY)   pos.y = maxY;

        line.setPosition(pos);

        //Handle Rotation
        line.setRotation(line.getRotation() - rotSpeed  * sf::Keyboard::isKeyPressed(sf::Keyboard::Up) * dt.asSeconds());
        line.setRotation(line.getRotation() + rotSpeed * sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * dt.asSeconds());
        t -= sf::Keyboard::isKeyPressed(sf::Keyboard::Up) * .01;
        t += sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * .01;
        if (t < 0) t = 0;
        if (t > 1) t = 1;

        //Trajectory
        auto cosRad = std::cos((float)line.getRotation() * ((3.14 * 2) / 360));
        auto sinRad = std::sin((float)line.getRotation() * ((3.14 * 2) / 360));

        plot(line.getPosition());
        plot(line.getPosition() + sf::Vector2f(
            cosRad * 250,
            sinRad * 250
        ));
        plot(line.getPosition() + sf::Vector2f(
            cosRad * 500,
            sinRad * 500 * std::abs(cosRad)
        ));
        plot(line.getPosition() + sf::Vector2f(
            cosRad * 700,
            0
        ));

        plot(Catmull::polynom2(
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




        //Update balls from canon
        for (int i = 0; i < balls.size();i++) {
            balls[i].setPosition(
                catmullLine.getPoint(ballsT[i]));
            ballsT[i] += dt.asSeconds();
            if (ballsT[i] >= .75) {
                balls.erase(balls.begin());
                ballsT.erase(ballsT.begin());
            }
        }


        // shoot VFX
        auto getAngle = [&](float pi) {
            return sf::Vector2f(std::cos(pi), std::sin(pi));
        };

        sf::Vector2f startPos(catmullLine.getPoint(0));
        sf::CircleShape mid(5);
        mid.setFillColor(sf::Color::Red);
        mid.setPosition(startPos);

        float distanceMin = 20;
        float distanceRand = 30;
        int qual = 16;
        sf::Vector2f posFix = sf::Vector2f(0, 0);
        sf::VertexArray explosion(sf::PrimitiveType::TriangleStrip, qual+1);
        if (isShooting) {
            for (int i = 0; i < qual; i++) {
                double t = (double)i / qual;
                t *= 3.14159 * 2;
                sf::CircleShape truc(5);
                explosion[i].position = startPos + getAngle(t) * (distanceMin + (float)Lib::rand() / RAND_MAX * distanceRand);
                if (i == 0) posFix = explosion[i].position;
            }
            explosion[qual].position = posFix;
        }

        //Background
        std::vector<sf::VertexArray> montagnes;
        int quality = 1200;
        float distanceBmontagne = 1;

        sf::Color topColor = sf::Color::White;
        sf::Color midColor(102,51,0);
        sf::Color botColor = sf::Color::Green;

        int pointCount = 9;
        float offset = -100;
        sf::VertexArray montagne(sf::LinesStrip, pointCount);
        montagne[0].position = sf::Vector2f(0,              offset + 100);
        montagne[1].position = sf::Vector2f(1920 * .125,    offset + 50);
        montagne[2].position = sf::Vector2f(1920 * .25,     offset + 25);
        montagne[3].position = sf::Vector2f(1920 * .375,    offset + 50);
        montagne[4].position = sf::Vector2f(1920 * .5,      offset + 100);
        montagne[5].position = sf::Vector2f(1920 * .625,    offset + 80);
        montagne[6].position = sf::Vector2f(1920 * .75,     offset + 25);
        montagne[7].position = sf::Vector2f(1920 * .875,    offset + 50);
        montagne[8].position = sf::Vector2f(1920,           offset + 100);

        for (int j = 0; j < pointCount; j++) {
            montagne[j].color = sf::Color::Cyan;
        }


        auto lerp = [](sf::Color c1, sf::Color c2, float t) {
            sf::Color nuColor(
                c1.r + t * (c2.r - c1.r),
                c1.g + t * (c2.g - c1.g),
                c1.b + t * (c2.b - c1.b)
            );
            return nuColor;
        };


        for (int i = 1; i < quality; i++) {
            sf::VertexArray mont(sf::LinesStrip, pointCount);
            for (int j = 0; j < pointCount; j++) {
                mont[j].position = montagne[j].position + sf::Vector2f(0, i * distanceBmontagne);
                auto t = (float)i / quality;
                if (t < 0.2f)
                    mont[j].color = sf::Color::Cyan;
                else if (t < 0.5f)
                    mont[j].color = lerp(topColor, midColor, (float)(t -0.2f) * 2.0f);
                else
                    mont[j].color = lerp(midColor, botColor, (float)(t - 0.5f) * 2.0f);
            }
            montagnes.push_back(mont);
        }
        montagnes.push_back(montagne);


        window.clear();
        for (auto m : montagnes) {
            window.draw(m);
        }
        window.draw(explosion);
        window.draw(mid);
        window.draw(shape);
        window.draw(shapeSoleil);
        window.draw(line);
        for(auto p : catmullPoints)
            window.draw(p);
        for(auto b : balls)
            window.draw(b);
        catmullLine.draw(window);
        window.display();
        catmullPoints.clear();
    }
};

int main() {
    testSFML();
    return 0;
};