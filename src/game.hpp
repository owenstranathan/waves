#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System.hpp>

class GameObject {
public:
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
};


class Game {
	// TODO: something here.
};

#endif // !GAME_HPP
