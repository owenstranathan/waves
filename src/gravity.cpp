#include "gravity.hpp"
#include "physicsbody.hpp"


Gravity::Gravity(Game* g) : game(g) {}
Gravity::~Gravity() {}

void Gravity::apply(PhysicsBody& pb, wabi::duration deltaTime) {
	pb.velocity += sf::Vector2f(0, constant * deltaTime.count());
}
