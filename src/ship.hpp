#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Ship : public PhysicsBody
{
public:
	Ship(Game *, sf::Vector2f, float, float);
	Ship(Game *, sf::Vector2f, sf::Vector2f);
	virtual ~Ship();

	virtual void accept(Visitor &) override;
	virtual void accept(CollisionVisitor &, Collidable *) override;
	virtual void collisionEnter(Sea *) override;
	virtual void collisionStay(Sea *) override;
	virtual void collisionEnter(Wave *) override;
	virtual void collisionStay(Wave *) override;
	virtual void collisionEnter(Platform *) override;
	virtual void collisionStay(Platform *) override;
	virtual void collisionExit(Platform *) override;

	virtual void update(const float) override;
	virtual wabi::Rectf rect() const override;

	float width;
	float height;
};
