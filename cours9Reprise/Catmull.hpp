#pragma once

#include "SFML/System/Vector2.hpp"

class Catmull{
public:
	static inline double polynom(
		double p0,
		double p1,
		double p2,
		double p3,

		double t
	) {
		double q = 2.0 * p1;
		double t2 = t * t;

		q += (-p0 + p2) * t;
		q += (2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * t2;
		q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

		return 0.5 * q;
	}; 

	static inline sf::Vector2f polynom2(
		sf::Vector2f p0,
		sf::Vector2f p1,
		sf::Vector2f p2,
		sf::Vector2f p3,
		double t
	) {
		return sf::Vector2f(
			polynom(p0.x, p1.x, p2.x, p3.x, t),
			polynom(p0.y, p1.y, p2.y, p3.y, t)
		);
	};
};