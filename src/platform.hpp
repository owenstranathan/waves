#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Platform : public PhysicsBody
{
public:
	// Platform() {}
	Platform(sf::Vector2f, float, float);
	virtual ~Platform();
	virtual wabi::Rectf rect() const override;
	virtual void accept(Visitor &) override;
	virtual void accept(CollisionVisitor &, Collidable *) override;
	virtual void collisionEnter(Ship *) override;
	virtual void collisionStay(Ship *) override;
	virtual void collisionExit(Ship *) override;

	float width;
	float height;
};
