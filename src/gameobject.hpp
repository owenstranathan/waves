#pragma once

#include "prelude.hpp"
#include "utils.hpp"

class GameObject {
public:
	GameObject();
	virtual ~GameObject() {}
	virtual void accept(Visitor&) = 0;
	virtual void update(const float) = 0;
	bool active = true;
	const int id;

	Game* game;
private:
	static int _seed_id;
};


