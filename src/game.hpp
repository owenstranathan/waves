#pragma once

#include <SFML/System.hpp>
#include "prelude.hpp"
#include "utils.hpp"
#include "collisionsystem.hpp"
#include "gravity.hpp"


class Game {
	// TODO: something here.
public:

	Game(float);
	~Game();

	void update();
	void handleEvent(sf::Event&);

	Rock* createRock(sf::Vector2f);
	std::list<Rock*>::iterator deleteRock(std::list<Rock*>::iterator it);
	std::list<Rock*>::iterator deleteRock(Rock *);

	Sea* sea;
	std::list<Wave*> waves;
	std::list<Rock*> rocks;
	bool over = false;
	bool won = false;

	CollisionSystem collisionSystem;
	Gravity gravity;

	wabi::Time time;

};

