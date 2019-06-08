#include "game.hpp"
#include "sea.hpp"
#include "rock.hpp"
#include "wave.hpp"


Game::Game(float seaLevel) : sea(new Sea(this, seaLevel)), collisionSystem(this), gravity(this), time() {
	collisionSystem.addCollider(sea);
}

Game::~Game() { 
	// collisionSystem.removeCollider(sea);
	delete sea;

}

void Game::update() {
	time.keepTime();
	sea->update(time.deltaTime);
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
	if (event.type == sf::Event::MouseButtonPressed){
		auto mousePosition = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		createRock(mousePosition);
	}

}
