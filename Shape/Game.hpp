#pragma once
#include <SFML/System.hpp>
struct Game {
public:
	static inline const sf::String NAME = "Shape !";
	static inline const bool DEBUG = true;
	static inline constexpr float WIDTH = 1920;
	static inline constexpr float HEIGHT = 1080;
	static inline constexpr float CELL_SIZE = 60;
	static float AREA_MARGE_X() {
		return (WIDTH - HEIGHT) * 0.5f;
	};
	static float AREA_MARGE_Y() {
		return CELL_SIZE * 0.5f;
	};
};