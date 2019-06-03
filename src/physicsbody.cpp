#include "physicsbody.hpp"

PhysicsBody::PhysicsBody() : mass(1) { }

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::fixedUpdate(wabi::duration deltaTime) {
	position += velocity;
	velocity += acceleration;
	acceleration = sf::Vector2f();
}
