#include "collidable.hpp"
#include "visitor.hpp"

void Collidable::accept(Visitor& v) { return v.visit(this); }

void Collidable::accept(CollisionVisitor& v, Collidable* c) { return v.visit(this, c); }

// collisionEnter
void Collidable::collisionEnter(Collidable* c) { }

void Collidable::collisionEnter(Sea* c) { }

void Collidable::collisionEnter(Ship* c) { }

void Collidable::collisionEnter(Rock* c) { }

void Collidable::collisionEnter(Wave* c) { }

// collisionStay
void Collidable::collisionStay(Collidable* c) { }

void Collidable::collisionStay(Sea* c) { }

void Collidable::collisionStay(Ship* c) { }

void Collidable::collisionStay(Rock* c) { }

void Collidable::collisionStay(Wave* c) { }

// collisionExit
void Collidable::collisionExit(Collidable* c) { }

void Collidable::collisionExit(Sea* c) { }

void Collidable::collisionExit(Ship* c) { }

void Collidable::collisionExit(Rock* c) { }

void Collidable::collisionExit(Wave* c) { }

