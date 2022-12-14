#pragma once
#include "SFML/Window/Event.hpp"

class Entity;

class State {
public:
	Entity*			owner = nullptr;
	virtual void	onEnterState() {};
	virtual void	onEvent(sf::Event& ev) {};
	virtual void	updateState() {};
};


class StateIdle : public State{
public:
	StateIdle(Entity * e){
		owner = e;
	}

	virtual void onEnterState() override;
	virtual void onEvent(sf::Event& ev) override;
	virtual void updateState() override;
};

class StateWalk : public State {
public:
	StateWalk(Entity* e) {
		owner = e;
	};

	virtual void onEnterState() override;
	virtual void onEvent(sf::Event& ev) override;
	virtual void updateState() override;
};