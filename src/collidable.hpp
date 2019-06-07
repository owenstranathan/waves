#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "gameobject.hpp"

class Collidable : public GameObject{
public:
	virtual void accept(Visitor& v);
	virtual sf::Rect<float> rect() const = 0;
};
