#pragma once
#include "prelude.hpp"
#include "utils.hpp"

class GameObject {
public:
	GameObject();
	virtual void * accept(Visitor&) = 0;
	virtual void update(wabi::duration deltaTime) = 0;
	bool active = true;
	const int id;
private:
	static int _seed_id;
};

