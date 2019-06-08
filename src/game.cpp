#include "game.hpp"
#include "sea.hpp"
#include "rock.hpp"


Game::Game(float seaLevel) : sea(new Sea(seaLevel)), collisionSystem(), time() {
	collisionSystem.addCollider(sea);
}

Game::~Game() { 
	// collisionSystem.removeCollider(sea);
	delete sea;
}

void Game::update() {
	time.keepTime();
	sea->update(time.deltaTime);
	for (auto it = rocks.begin(); it != rocks.end(); ++it) {
		auto rock = *it;
		gravity.apply(*rock, time.deltaTime);
		rock->update(time.deltaTime);
		if (rock->position.y > SCREEN_HEIGHT || rock->position.x > SCREEN_WIDTH || rock->position.x < 0 || rock->position.y < 0) {
			it = deleteRock(rock);
			if (it == rocks.end())
				break;
		}
	}
	collisionSystem.resolveCollisions();
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

Rock* Game::createRock(sf::Vector2f position) {
		auto rock = new Rock(50);
		rock->position = position;
		rocks.push_back(rock);
		collisionSystem.addCollider(rock);
		return rock;
}

void Game::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed){
		auto mousePosition = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		createRock(mousePosition);
	}

}
