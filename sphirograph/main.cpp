#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
static int screenX = 1920;
static int screenY = 1080;



int main() {

    //Set nb of arms
    int nbArms = 0;
    cout << "Number of arms : ";
    cin >> nbArms;

    //Set arms length
    vector<int> armsLength;
    for (int i = 0; i < nbArms; i++) {
        int armLength = 0;
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


    sf::RenderWindow window(sf::VideoMode(screenX, screenY), "SFML works!");


    sf::Clock time;
    while (window.isOpen()) {
        sf::Event event;
        sf::Time dt = time.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
};