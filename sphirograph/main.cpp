using namespace std;

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sphirograph.hpp"

static float screenX = 1920;
static float screenY = 1080;
static string projectName = "Sphirograph";

//Nomenclature : nbArms; armLength n, armLength n+1, ...; armAngularSpeed n, armAngularSpeed n+1, ...;
//List de truc sympa :      
// 2; 100, 100; 25, 44;
// 2; 100, 45; 30, -50;
// 2; 142, 20; 20, -142;
// 2; 105, 50; 50, 105;
// 2; 100, 50; 30, -80;
// 10; 20; 10, -11, 12, -13, 14, -15, 16, -17, 18, -19;
// 19; 10; 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1;
// 3; 40; 10, -10, 30;
// 10; 10, 10, 20, 10, 20, 10, 20, 10, 20, 10; 1, 6, 5, 3, 1, 7, 3, 2, 1, 3;
// 4; 10, 10, 30, 30; -40, 10, 30, -50;
// 3: 38, 96, 11; 98, -32, 97;


int main() {

    //Set nb of arms
    int nbArms = 0;
    cout << "Number of arms : ";
    cin >> nbArms;

    //Set arms length
    vector<float> armsLength;
    for (int i = 0; i < nbArms; i++) {
        float armLength = 0;
        cout << "Length for arm " << i + 1 << " : ";
        while (armLength == 0) {
            cin >> armLength;
            if (armLength != 0) {
                armLength = abs(armLength);
                armsLength.push_back(armLength);
            }
        }
    }

    //Set arms angular velocity
    vector<double> armsAngularVelocity;
    for (int i = 0; i < nbArms; i++) {
        double armAngularVelocity = 0;
        cout << "Angular Velocity (deg/s) of arm " << i + 1 << " : ";
        while (armAngularVelocity == 0) {
            cin >> armAngularVelocity;
            if (armAngularVelocity != 0) {
                armAngularVelocity *= (2 * 3.14159) / 360;
                armsAngularVelocity.push_back(armAngularVelocity);
            }
        }
    }


    sf::RenderWindow window(sf::VideoMode(screenX, screenY), projectName);


    Sphirograph shirograph(
        sf::Vector2f(screenX * 0.5f, screenY * 0.5f),
        &nbArms, &armsLength, &armsAngularVelocity,
        sf::Color::Green, sf::Color::Magenta
        );


    //TimeScale
    float speed = 1;
    float minSpeed = 0.5f;
    float maxSpeed = 10;


    //Create Text
    sf::Font font;
    if (!font.loadFromFile("Assets/courier-new.ttf")) return EXIT_FAILURE;
    sf::Text speedText;
    speedText.setPosition(screenX * 0.05, screenY * 0.05);
    speedText.setFont(font);
    speedText.setCharacterSize(30);
    speedText.setFillColor(sf::Color::White);

    bool drawArms = true;


    sf::Clock time;
    while (window.isOpen()) {
        sf::Event event;
        sf::Time dt = time.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //Set Timescale
            speed += sf::Keyboard::isKeyPressed(sf::Keyboard::Up)   * 0.5f;
            speed -= sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * 0.5f;
            if (speed < minSpeed) speed = minSpeed;
            if (speed > maxSpeed) speed = maxSpeed;

            //Set drawArms
            drawArms = !sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }

        shirograph.update(dt.asSeconds() * speed);
        speedText.setString("Timescale : " + to_string(speed));

        window.clear();
        shirograph.draw(&window, drawArms);
        window.draw(speedText);
        window.display();
    }

    return 0;
};