#include "physicsbody.hpp"
#include "visitor.hpp"

PhysicsBody::PhysicsBody() : mass(1) { }

PhysicsBody::~PhysicsBody() { }


void PhysicsBody::update(wabi::duration deltaTime) {
	position += velocity;
	velocity += acceleration;
	acceleration = sf::Vector2f();
}
