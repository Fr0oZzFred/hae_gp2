#pragma once

#include "Entities.hpp"

class World{
public:
	World();

	bool collides(float x, float y);
};

extern World world;
