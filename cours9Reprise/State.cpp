#include "State.hpp"
#include "Entities.hpp"

inline static bool isCloseTo( float val, float target, float eps = 1e-3){
	return abs(target - val) < eps;
}

void StateIdle::onEnterState() {
	owner->shp->setFillColor(sf::Color::Yellow);
	owner->dx = 0;
	owner->dy = 0;
}

void StateIdle::onEvent(sf::Event& event) {

}

void StateIdle::updateState() {
	owner->walkControl();
	 
	if (owner->dx != 0) {
		if ((abs(owner->dy) >= 0.01f))
			owner->changeState(owner->walkState);
	}
}


void StateWalk::onEnterState() {
	owner->shp->setFillColor(sf::Color::Green);

}

void StateWalk::onEvent(sf::Event& event) {
	//owner->jumpControl(event);
}

void StateWalk::updateState() {
	owner->walkControl();
	if (isCloseTo(owner->dx,0) && isCloseTo(owner->dy, 0)) {
		owner->changeState(owner->idleState);
	}
}


