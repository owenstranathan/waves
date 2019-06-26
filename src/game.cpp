#include <iostream>

#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rock.hpp"
#include "wave.hpp"

const float Game::worldWidth = 128; // meters
const float Game::worldHeight = 72; // meters

Game::Game(float seaLevel) : 
	sea(new Sea(this, seaLevel)), ship(new Ship(this, sf::Vector2f(worldWidth/2, worldHeight), 5, 3)),
	collisionSystem(this), time() {
	collisionSystem.addCollider(sea);
	collisionSystem.addCollider(ship);
}

Game::~Game() { 
	collisionSystem.removeCollider(sea);
	collisionSystem.removeCollider(ship);
	delete sea;
	delete ship;
}

void Game::update() {
	time.keepTime();
	timeSinceLastUpdate += time.deltaTime.count();
	//if (timeSinceLastUpdate >= fixedStep) {
	sea->update(time.deltaTime);
	ship->update(time.deltaTime);
	// Housekeeping.. killing rocks and waves
	for (auto it = waves.begin(); it != waves.end(); std::advance(it, 1)) {
		auto wave = *it;
		wave->update(time.deltaTime);
		if (!wave->active)
			it = deleteWave(wave);
		if (it == waves.end())
			break;
	}
	for (auto it = rocks.begin(); it != rocks.end(); ++it) {
		auto rock = *it;
		rock->update(time.deltaTime);
		if (!rock->active)
			it = deleteRock(rock);
		if (it == rocks.end())
			break;
	}
	collisionSystem.resolveCollisions();
	timeSinceLastUpdate = 0.f;
}


Wave* Game::createWave(float position, float magnitude) {
	Wave * wave = new Wave(this, position, magnitude);
	waves.push_back(wave);
	collisionSystem.addCollider(wave);
	return wave;
}


std::list<Wave*>::iterator Game::deleteWave(std::list<Wave*>::iterator it) {
	auto wave = *it;
	collisionSystem.removeCollider(wave);
	it = waves.erase(it);
	delete wave;
	return it;
}

std::list<Wave*>::iterator Game::deleteWave(Wave* wave) {
	auto search = std::find(waves.begin(), waves.end(), wave);
	return (search != waves.end()) ? deleteWave(search) : waves.end();
}

Rock* Game::createRock(sf::Vector2f position) {
	auto rock = new Rock(this, 50);
	rock->position = position;
	rocks.push_back(rock);
	collisionSystem.addCollider(rock);
	return rock;
}

std::list<Rock*>::iterator Game::deleteRock(std::list<Rock*>::iterator it) {
	auto rock = *it;
	collisionSystem.removeCollider(rock);
	it = rocks.erase(it);
	delete rock;
	return it;
}

std::list<Rock*>::iterator Game::deleteRock(Rock* rock) {
	auto search = std::find(rocks.begin(), rocks.end(), rock);
	return (search != rocks.end()) ? deleteRock(search) : rocks.end();
}


void Game::handleEvent(sf::Event& event) {
	static bool mousePressed = false;
	static sf::Vector2f mousePosition;
	if (event.type == sf::Event::MouseButtonPressed && ! mousePressed) {
		// mousePosition = screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		// mousePressed = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		// createRock(mousePosition);
		// mousePressed = false;
	}
	else if (event.type == sf::Event::KeyPressed) {
	}
}
