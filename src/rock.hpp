#ifndef ROCK_HPP
#define ROCK_HPP

#include "utils.hpp"
#include "physicsbody.hpp"

static const float ROCK_MASS = 5.f;


class Rock : public PhysicsBody {
public:
	Rock(float r): radius(r) {
		mass = ROCK_MASS;
	}

	virtual void accept(Visitor&);
	virtual sf::Rect<float> rect() const;
	float radius;
};

#endif // !ROCK_HPP
