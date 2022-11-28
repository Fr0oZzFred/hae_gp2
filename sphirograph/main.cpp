using namespace std;

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sphirograph.hpp"

static float screenX = 1920;
static float screenY = 1080;
static string projectName = "Sphirograph";



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
        cout << "Angular Velocity (deg/s)  of arm " << i + 1 << " : ";
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