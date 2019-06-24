#include <iostream>

#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rock.hpp"
#include "wave.hpp"


Game::Game(float seaLevel) : sea(new Sea(this, seaLevel)), ship(new Ship(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT -200 ), 75, 75)), collisionSystem(this), gravity(this), time() {
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
	sea->update(time.deltaTime);
	gravity.apply(*ship, time.deltaTime);
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
		gravity.apply(*rock, time.deltaTime);
		rock->update(time.deltaTime);
		if (!rock->active)
			it = deleteRock(rock);
		if (it == rocks.end())
			break;
	}

	collisionSystem.resolveCollisions();
	auto max_size = 1000;
	if (log.str().size() > max_size) {
		log.clear();
	}
}

Wave* Game::createWave(float position, float magnitude) {
	Wave * wave = new Wave(this, position, magnitude);
	waves.push_back(wave);
	// wabi::insert_sorted(waves, wave, [](Wave * a, Wave * b)->bool {return a->rect().left < b->rect().left; });
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
		mousePosition = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		mousePressed = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
	// if (event.type == sf::Event::MouseButtonReleased) {
		createRock(mousePosition);
		// auto currMousePos = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		// auto size = sf::Vector2f(currMousePos.x - mousePosition.x, currMousePos.y - mousePosition.y);
		// auto absSize = sf::Vector2f(std::abs(size.x), abs(size.y));
		// auto xSign = size.x / abs(size.x);
		// auto ySign = size.y / abs(size.y);
		// Ship* ship;
		// if (xSign > 0 && ySign < 0) {		
		// 	ship = new Ship(mousePosition, absSize);
		// }
		// else if (xSign > 0 && ySign > 0) {
		// 	auto startPos = sf::Vector2f(mousePosition.x, mousePosition.y + absSize.y);
		// 	ship = new Ship(startPos, absSize);
		// }
		// else if(xSign < 0 && ySign > 0) {
		// 	ship = new Ship(currMousePos, absSize);
		// }
		// else{ // (xSign < 0 && ySign < 0) {
		// 	auto startPos = sf::Vector2f(currMousePos.x, currMousePos.y + absSize.y);
		// 	ship = new Ship(startPos, absSize);
		// }
		// collisionSystem.addCollider(ship);
		mousePressed = false;
	}
	else if (event.type == sf::Event::KeyPressed) {
		// std::cout << event.key.code << std::endl;
		// switch (event.key.code)
		// {
		// case sf::Keyboard::C:
		// 	collisionSystem.clear();
		// default:
		// 	break;
		// }
	}
}
