#pragma once
#include "prelude.hpp"
#include "utils.hpp"

class GameObject {
public:
	virtual void * accept(Visitor&) = 0;
	virtual void update(wabi::duration deltaTime) = 0;
};

