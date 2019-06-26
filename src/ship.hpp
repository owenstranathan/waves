#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Ship : public PhysicsBody{
public:	

	Ship(Game*, sf::Vector2f, float, float);
	Ship(Game*, sf::Vector2f, sf::Vector2f);
	~Ship();

	virtual void accept(Visitor&) override;
	virtual void accept(CollisionVisitor&, Collidable*) override;
	virtual void resolveCollision(Sea * c) override;
	virtual void update(const wabi::duration&) override;
	virtual wabi::Rectf rect() const override;

	float width;
	float height;
};
