#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"


//--------- / Interfaces / ---------// 

class Visitor;
class GameObject;
class Collidable;
class PhysicsBody;


//--------- / Objects / ---------// 
class Sea;
class Rock;
class Wave;


//--------- / Systems / ---------// 

class Game;
class CollisionSystem;
class Gravity;
