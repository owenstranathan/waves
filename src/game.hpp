#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System.hpp>
#include "utils.hpp"

class GameObject {
public:
	virtual void update(wabi::duration deltaTime) {};
	virtual void fixedUpdate(wabi::duration deltaTime) {};
};


class Game {
	// TODO: something here.
};

#endif // !GAME_HPP
