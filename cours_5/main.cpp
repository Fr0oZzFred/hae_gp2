#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Lib.hpp"
#include "Catmull.hpp"
#include "Line.hpp"
#include "Entity.hpp"
#include "Bloom.hpp"
#include "HotReloadShader.hpp"
static const sf::String projectName = "Casse birque sans physic";
static const sf::Vector2f screenSize(1920, 1080);

static HotReloadShader* bloomShader = nullptr;
static HotReloadShader* blurShader = nullptr;

int main() {
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), projectName);
    Pad pad(sf::Vector2f(screenSize.x * .5, screenSize.y * .75));

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
   
   float bloomWidth = 48;
   sf::Glsl::Vec4 bloomMul(1, 1, 1, 0.8);




    Ball ball(&pad);
    int padSpeed = 500;
    int ballSpeed = 500;
    bool gameStarted = false;

    std::vector<Block> blocks;
    int c = 8;
    int r = 4;
    for (int x = 0; x < c; x++) {
        for (int y = 0; y < r; y++) {
            Block block(sf::Vector2f(screenSize.x * x/c, screenSize.y  * 0.5f * y/r));
            blocks.push_back(block);
        }
    }

    std::vector<Particle> particles;


    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                gameStarted = true;
        }


        if (gameStarted) {
            pad.Move(padSpeed, dt, screenSize);
            ball.Move(ballSpeed, dt, screenSize);
            if (ball.shape->getPosition().y > screenSize.y * .8) {
                return 0;
            }
        }
            
        pad.DetectColision(&ball);
        for (auto &b : blocks) {
            b.DetectColision(&ball);
            if (b.touched) {
                b.touched = false;
                bool found = false;
                for (auto &part : particles) {
                    if (!part.used) {
                        part.Reset(b.originalPos);
                        found = true;
                        break;
                    }
                }
                if(!found){
                    Particle p(b.originalPos);
                    particles.push_back(p);
                }
            }
        }

        for (auto& p : particles)   p.Update(dt);

        window.clear();

        for (auto &b : blocks)      window.draw(*b.shape);
        for (auto p : particles) {
            window.draw(p.shape);
            for (auto r : p.rects)
                window.draw(*r.shape);
        }
        window.draw(*pad.shape);
        window.draw(*ball.shape);

        if (bloomWidth)
            Bloom::render(window, winTex, destX, destFinal, &blurShader->sh, &bloomShader->sh, bloomWidth, bloomMul);

        window.display();
    }

    return 0;
};