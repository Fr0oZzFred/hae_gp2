#pragma once
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

class BackGround {
public:

	BackGround(int startPattern, sf::Clock* _time);

	sf::VertexArray background;
	int pattern = 0;
	float patternTime = 5.0f;
	float transitionTime = 5.0f;
	sf::Clock* time = nullptr;

	std::function<void()> shape = std::bind(std::mem_fn(&BackGround::Lines), this);

	void update();
	float getTime();

	void Lines();

	void draw(sf::RenderWindow& win);
};