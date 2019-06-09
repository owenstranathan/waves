#pragma once

#include <sstream>
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

	Wave * createWave(float position, float magnitude);
	std::list<Wave*>::iterator deleteWave(std::list<Wave*>::iterator);
	std::list<Wave*>::iterator deleteWave(Wave*);

	Rock* createRock(sf::Vector2f);
	std::list<Rock*>::iterator deleteRock(std::list<Rock*>::iterator);
	std::list<Rock*>::iterator deleteRock(Rock *);

	Sea* sea;
	std::list<Wave*> waves;
	std::list<Rock*> rocks;
	CollisionSystem collisionSystem;
	Gravity gravity;
	wabi::Time time;
	std::stringstream log;
	bool over = false;
	bool won = false;
};

