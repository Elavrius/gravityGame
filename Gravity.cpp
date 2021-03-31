#include "Gravity.h"
#include <math.h>

int Gravity::gravityForce = 100;

double Gravity::distance(Planet& p1, Planet& p2)
{
	return sqrt(pow(p2.getPosX()-p1.getPosX(), 2) + pow(p2.getPosY()-p1.getPosY(),2));
}

void Gravity::applyGravity(Planet& p1, Planet& p2, double deltaTime)
{
	double forceDistance = Gravity::distance(p1, p2);
	if (forceDistance < 0) {
		forceDistance *= -1;
	}
	double spaceDistance = forceDistance;

	if (forceDistance < 10) {
		forceDistance = 10;
	}
	if (spaceDistance < 1) {
		spaceDistance = 1;
	}

	double force = (deltaTime * gravityForce * p1.getMass() * p2.getMass()) / pow(forceDistance, 2);

	double vectorX = (p2.getPosX() - p1.getPosX())/spaceDistance;
	double vectorY = (p2.getPosY() - p1.getPosY())/spaceDistance;

	double p1Acceleration = force / p1.getMass();
	double p2Acceleration = force / p2.getMass();

	p1.velocityX += (vectorX * p1Acceleration);
	p1.velocityY += (vectorY * p1Acceleration);

	p2.velocityX += (vectorX * -1 * p2Acceleration);
	p2.velocityY += (vectorY * -1 * p2Acceleration);
}
