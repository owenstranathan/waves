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
			it = rocks.erase(it);
			if (it == rocks.end())
				break;
			// it = rocks.(rock);
			delete rock;
		}
	}
}


void Game::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed){
		auto mousePosition = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
		auto rock = new Rock(50);
		rock->position = mousePosition;
		rocks.push_back(rock);
	}

}
