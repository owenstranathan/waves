#include "physicsbody.hpp"

void PhysicsBody::fixedUpdate() {
	position += velocity;
	velocity += acceleration;
	acceleration = sf::Vector2f();
}
