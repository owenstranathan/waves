#include "collidable.hpp"
#include "visitor.hpp"

void Collidable::accept(Visitor& v) { v.visit(this); }
