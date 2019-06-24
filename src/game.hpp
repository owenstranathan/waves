#pragma once

#include <sstream>
#include <SFML/System.hpp>
#include "prelude.hpp"
#include "utils.hpp"
#include "collisionsystem.hpp"
#include "gravity.hpp"
#include "graphics.hpp"

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
	Ship* ship;
	std::list<Wave*> waves;
	std::list<Rock*> rocks;
	CollisionSystem collisionSystem;
	Gravity gravity;
	wabi::Time time;
	std::stringstream log;
	bool over = false;
	bool won = false;
	static const float worldWidth;
	static const float worldHeight;
};

template <typename T>
inline sf::Vector2<T> brainToScreenSpace(const sf::Vector2<T> in) {
	return sf::Vector2<T>(in.x, (SCREEN_HEIGHT - in.y));
}

template <typename T>
inline sf::Vector2<T> screenToBrainSpace(const sf::Vector2<T> in) {
	return sf::Vector2<T>(in.x, abs(SCREEN_HEIGHT - in.y));
}

template <typename T>
inline sf::Vector2<T> toWorld(const sf::Vector2<T> in) {
	// TODO: fuck. implement scalign
	return screenToBrainSpace(in) / Graphics::worldToScreenRatio;
}

template <typename T>
inline  sf::Vector2<T> toScreen(const sf::Vector2<T> in) {
	// TODO: fuck. implement scalign
	auto v = sf::Vector2<T>(in.x * Graphics::worldToScreenRatio, (Game::worldHeight - in.y) * Graphics::worldToScreenRatio)
	return * Graphics::worldToScreenRatio;
}

