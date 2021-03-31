#pragma once
#include "Planet.h"
class Gravity
{
public:
	static double distance(Planet &p1,Planet &p2);
	static void applyGravity(Planet& p1, Planet& p2, double deltaTime);
	static int gravityForce;
};

