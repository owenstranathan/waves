#include <iostream>
#include <limits>

#include "game.hpp"
#include "graphics.hpp"
#include "platform.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rock.hpp"
#include "wave.hpp"

const float Game::worldWidth = 128; // meters
const float Game::worldHeight = 72; // meters

Game::Game(float seaLevel) : sea(new Sea(this, seaLevel)), ship(new Ship(this, sf::Vector2f(worldWidth / 2 - 10, worldHeight -1.f), 5, 3)),
							 collisionSystem(this)
{
	// platforms.push_back(new Platform(sf::Vector2f(2 * worldWidth / 3, worldHeight/2), 10, worldHeight / 2));
	platforms.push_back(new Platform(sf::Vector2f(3 * worldWidth / 6 , worldHeight/3), 20, 10));
	for (auto && p : platforms) {
		collisionSystem.addCollidable(p);
	}
	collisionSystem.addCollidable(sea);
	collisionSystem.addCollidable(ship);
}

Game::Game(Sea*, Ship*, std::list<Platform*>) : sea(nullptr), ship(nullptr), collisionSystem(this) {}

Game::~Game()
{
	collisionSystem.removeCollidable(sea);
	collisionSystem.removeCollidable(ship);
	delete sea;
	delete ship;
}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();
	timeSinceLastUpdate += deltaTime;
	if (timeSinceLastUpdate >= fixedStep)
	{
		cleanUp();
		deltaTime = timeSinceLastUpdate;
		// It's important to resolve collisions first, so that the collision appears in the update.
		collisionSystem.resolveCollisions();
		sea->update(deltaTime);
		ship->update(deltaTime);
		if (!ship->active)
		{
			ship->position = sf::Vector2f(worldWidth / 2, worldHeight / 3);
			ship->active = true;
			// over = true;
		}
		// Housekeeping.. killing rocks and waves
		for (auto &&wave : waves)
		{
			wave->update(deltaTime);
		}
		for (auto &&rock : rocks)
		{
			rock->update(deltaTime);
		}
		timeSinceLastUpdate = 0.f;
	}
}

Wave *Game::createWave(float position, float magnitude)
{
	Wave *wave = new Wave(this, position, magnitude);
	waves.push_back(wave);
	collisionSystem.addCollidable(wave);
	return wave;
}

std::list<Wave *>::iterator Game::deleteWave(std::list<Wave *>::iterator it)
{
	auto wave = *it;
	collisionSystem.removeCollidable(wave);
	it = waves.erase(it);
	delete wave;
	return it;
}

std::list<Wave *>::iterator Game::deleteWave(Wave *wave)
{
	auto search = std::find(waves.begin(), waves.end(), wave);
	return (search != waves.end()) ? deleteWave(search) : waves.end();
}

Rock *Game::createRock(sf::Vector2f position)
{
	auto rock = new Rock(this, 1.5);
	rock->position = position;
	rocks.push_back(rock);
	collisionSystem.addCollidable(rock);
	return rock;
}

std::list<Rock *>::iterator Game::deleteRock(std::list<Rock *>::iterator it)
{
	auto rock = *it;
	collisionSystem.removeCollidable(rock);
	it = rocks.erase(it);
	delete rock;
	return it;
}

std::list<Rock *>::iterator Game::deleteRock(Rock *rock)
{
	auto search = std::find(rocks.begin(), rocks.end(), rock);
	return (search != rocks.end()) ? deleteRock(search) : rocks.end();
}

void Game::handleEvent(sf::Event &event)
{
	static bool mousePressed = false;
	static sf::Vector2f mousePosition;
	if (event.type == sf::Event::MouseButtonPressed && !mousePressed)
	{
		mousePosition = (sf::Vector2f)Graphics::screen2GamePos(sf::Mouse::getPosition());
		mousePressed = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		createRock(mousePosition);
		mousePressed = false;
	}
	else if (event.type == sf::Event::KeyPressed)
	{
	}
}

void Game::cleanUp()
{
	for (auto it = waves.begin(); it != waves.end(); std::advance(it, 1))
	{
		auto wave = *it;
		if (!wave->active)
			it = deleteWave(wave);
		if (it == waves.end())
			break;
	}
	for (auto it = rocks.begin(); it != rocks.end(); ++it)
	{
		auto rock = *it;
		if (!rock->active)
			it = deleteRock(rock);
		if (it == rocks.end())
			break;
	}
}
