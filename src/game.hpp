#pragma once

#include <sstream>
#include <SFML/System.hpp>
#include "prelude.hpp"
#include "utils.hpp"
#include "collisionsystem.hpp"
#include "gravity.hpp"
#include "graphics.hpp"

class Game {
public:

	Game(float);
	~Game();

	void update();
	void handleEvent(sf::Event&);
	void cleanUp();

	Wave * createWave(float position, float magnitude);
	std::list<Wave*>::iterator deleteWave(std::list<Wave*>::iterator);
	std::list<Wave*>::iterator deleteWave(Wave*);

	Rock* createRock(sf::Vector2f);
	std::list<Rock*>::iterator deleteRock(std::list<Rock*>::iterator);
	std::list<Rock*>::iterator deleteRock(Rock *);

	Sea* sea;
	Ship* ship;
	std::list<Wave*> waves;
	std::list<Rock*> rocks;
	std::list<Platform*> platforms;
	CollisionSystem collisionSystem;
	sf::Clock clock;
	float deltaTime = 0.f;
	std::stringstream log;
	bool over = false;
	bool won = false;
	static const float worldWidth;
	static const float worldHeight;
	const float fixedStep = 0.002555f;
	float timeSinceLastUpdate = 0.0f;
};
