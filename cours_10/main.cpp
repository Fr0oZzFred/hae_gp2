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
#include "WorldFile.hpp"
#include "Dijkstra.hpp"

static float screenX = 1920;
static float screenY = 1080;

int main() {

    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Grid");
    sf::Clock t;
    float time = 0;

    vector<Entity> entities;

    ImGui::SFML::Init(window);
    Entity cube(new sf::RectangleShape(sf::Vector2f(16,16)),
        sf::Vector2f(Cst::SCREEN_SIZE_X * 0.4f,Cst::SCREEN_SIZE_Y * 0.4f),
        &entities);

    sf::Vector2i obj;
    sf::VertexArray objCase;
    objCase.setPrimitiveType(sf::Quads);
    auto toCase = [&](sf::Vector2i pos) {
        sf::Color col = sf::Color::Yellow;
        objCase.clear();
        objCase.append(sf::Vertex(sf::Vector2f(pos.x * Cst::CELL_SIZE, pos.y * Cst::CELL_SIZE), col));
        objCase.append(sf::Vertex(sf::Vector2f((pos.x + .9) * Cst::CELL_SIZE, pos.y * Cst::CELL_SIZE), col));
        objCase.append(sf::Vertex(sf::Vector2f((pos.x + .9) * Cst::CELL_SIZE, (pos.y + .9) * Cst::CELL_SIZE), col));
        objCase.append(sf::Vertex(sf::Vector2f(pos.x * Cst::CELL_SIZE, (pos.y + .9) * Cst::CELL_SIZE), col));
    };

    float color[4] = { 1.0,1.0,1.0,1.0 };
    
    float mat4_Array[16] = {
            0.3588, 0.7044, 0.1368, 0.0,
            0.2990, 0.5870, 0.1140, 0.0,
            0.2392, 0.4696, 0.0912 ,0.0,
            0,      0,      0,      1.0 
    };
    

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                world.statics.clear();
                world.statics = WorldFile::load("res/walls.txt");
                world.mkGraphics();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                WorldFile::save("res/walls.txt", world.statics);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                int idx = 0;
                dijkstra.g.clear();
                dijkstra.gd.clear();
                for (int x = 0; x < 1 + Cst::SCREEN_SIZE_X / Cst::CELL_SIZE; x++) {
                    for (int y = 0; y < 1 + Cst::SCREEN_SIZE_Y / Cst::CELL_SIZE; y ++) {
                        if (!world.collides(x, y)) dijkstra.add(sf::Vector2i(x, y));
                    }
                }
                dijkstra.mkGraphGraphics();
                obj = sf::Vector2i(64,32);
                dijkstra.shortestWay(sf::Vector2i(cube.cx, cube.cy), obj);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))    cube.jump();

        cube.update();

        bool b = true;
        ImGui::Begin("debug", &b);
        cube.im();
        ImGui::End();

        toCase(obj);

        ImGui::Begin("Shader", &b);
        using namespace ImGui;
        ColorPicker4("Color", &color[0]);
        Spacing();
        Spacing();
        Spacing();
        Text("Matrix");
        DragFloat4("0", &mat4_Array[0]);
        DragFloat4("1", &mat4_Array[4]);
        DragFloat4("2", &mat4_Array[8]);
        DragFloat4("3", &mat4_Array[12]);

        ImGui::End();


        sf::Texture tex;
        tex.loadFromFile("Eevee.png");
        sf::RectangleShape circleShape(sf::Vector2f(tex.getSize()));
        circleShape.setPosition(Cst::SCREEN_SIZE_X * .5f, Cst::SCREEN_SIZE_Y * .5f);
        sf::Shader shader;
        circleShape.setTexture(&tex);
        if (shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")) {
            shader.setUniform("time", time);
            shader.setUniform("color", sf::Glsl::Vec4(color[0],color[1],color[2],color[3]));
            shader.setUniform("matrix", sf::Glsl::Mat4(mat4_Array));
            shader.setUniform("texture", sf::Shader::CurrentTexture);
            time += dt.asSeconds();
        }



        window.clear();

        world.draw(window);
        dijkstra.draw(window);
        window.draw(objCase);
        window.draw(circleShape, & shader);
        ImGui::SFML::Render(window);
        cube.draw(&window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
};