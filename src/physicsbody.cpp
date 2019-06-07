#include "physicsbody.hpp"
#include "visitor.hpp"

PhysicsBody::PhysicsBody() : mass(1) { }

PhysicsBody::~PhysicsBody() { }

void PhysicsBody::accept(Visitor& v) { v.visit(this); }

void PhysicsBody::update(wabi::duration deltaTime) {
	position += velocity;
	velocity += acceleration;
	acceleration = sf::Vector2f();
}
