#include "physicsbody.hpp"
#include "utils.hpp"
#include "gravity.hpp"
#include "visitor.hpp"

PhysicsBody::PhysicsBody() { }

PhysicsBody::PhysicsBody(sf::Vector2f p) : position(p){ }

PhysicsBody::~PhysicsBody() { }


void PhysicsBody::update(wabi::duration deltaTime) {
	position += velocity;
	velocity += acceleration;
	acceleration = sf::Vector2f(0, 0);
}

void PhysicsBody::drag(float dragCoefficient = 1)
{
	sf::Vector2f dragForce = dragCoefficient * sf::Vector2f( -1 * wabi::sign(velocity.x) * (velocity.x * velocity.x), -1 * wabi::sign(velocity.y) *  (velocity.y * velocity.y));
	addForce(dragForce);
	// acceleration +=  -0.05f * sf::Vector2f(0, velocity.y * velocity.y) * wabi::Time::deltaTime.count();
}
