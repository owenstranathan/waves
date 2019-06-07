#include "gravity.hpp"
#include "physicsbody.hpp"


Gravity::Gravity() {}
Gravity::~Gravity() {}

void Gravity::apply(PhysicsBody& pb, wabi::duration deltaTime) {
	pb.velocity += sf::Vector2f(0, constant * deltaTime.count());
}
