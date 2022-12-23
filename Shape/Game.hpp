#pragma once
#include <SFML/System.hpp>
struct Game {
public:
	static const sf::String NAME;
	static const float WIDTH;
	static const float HEIGHT;
	static inline constexpr float CELL_SIZE = 60;
	static float AREA_X_SIDE();
	static float AREA_Y_SIDE();
};