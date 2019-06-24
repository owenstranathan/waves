#include "collidable.hpp"
#include "visitor.hpp"

void Collidable::accept(Visitor& v) { return v.visit(this); }

void Collidable::accept(CollisionVisitor& v, Collidable* c) { return v.visit(this, c); }

void Collidable::resolveCollision(Collidable* c) { }

void Collidable::resolveCollision(Sea* c) { }

void Collidable::resolveCollision(Ship* c) { }

void Collidable::resolveCollision(Rock* c) { }

void Collidable::resolveCollision(Wave* c) { }
