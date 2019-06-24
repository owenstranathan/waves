#include "gravity.hpp"
#include "physicsbody.hpp"

const float Gravity::constant = -19.8f;

Gravity::Gravity(Game* g) : game(g) {}
Gravity::~Gravity() {}

void Gravity::apply(PhysicsBody& pb, wabi::duration deltaTime) {
	// pb.velocity += sf::Vector2f(0, constant * deltaTime.count());
	pb.addForce(sf::Vector2f(0, constant));
}
