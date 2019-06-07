#include "gameobject.hpp"
#include "visitor.hpp"


void GameObject::accept(Visitor& v) { v.visit(this); }
