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
class Ship;
class Platform;


//--------- / Systems / ---------// 

class Game;
class CollisionSystem;
class Gravity;
