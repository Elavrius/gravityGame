#include "Planet.h"
#include "Utils.h"

double reflectionIndex = -0.5;

Planet::Planet(SDL_Renderer& renderer, double posX, double posY, int radius, int screenWidth, int screenHeight, bool moveable)
{
    this->moveable = moveable;
	this->renderer = &renderer;
	this->posX = posX;
	this->posY = posY;
	this->radius = radius;
    this->velocityX = 0;
    this->velocityY = 0;
    this->mass = radius * radius * radius;
    UPPER_BORDER = 0 + radius;
    BOTTOM_BORDER = screenHeight - radius;
    LEFT_BORDER = 0 + radius;
    RIGHT_BORDER = screenWidth - radius;
}

void Planet::move(double deltaTime)
{
    if (moveable) {
        double deltaX = velocityX * deltaTime;
        double deltaY = velocityY * deltaTime;
        double newposY = posY + deltaY;
        double newposX = posX + deltaX;
        bool collisionY = false;
        bool collisionX = false;
        if (newposY < UPPER_BORDER) {
            velocityY *= reflectionIndex;
            posY += -newposY + (double)UPPER_BORDER;
            collisionY = true;
        }
        else if (newposY > BOTTOM_BORDER) {
            velocityY *= reflectionIndex;
            posY += (double)BOTTOM_BORDER - newposY;
            collisionY = true;
        }
        if (posX < LEFT_BORDER) {
            velocityX *= reflectionIndex;
            posX += -newposX + (double)LEFT_BORDER;
            collisionX = true;
        }
        else if (newposX > RIGHT_BORDER) {
            velocityX *= reflectionIndex;
            posX += (double)RIGHT_BORDER - newposX;
            collisionX = true;
        }
        if (!collisionX) {
            this->posX += deltaX;
        }
        if (!collisionY) {
            this->posY += deltaY;
        }
    }
	
}

void Planet::draw()
{
    if (!moveable) {
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    drawCircle(renderer, posX, posY, radius);

}

double Planet::getPosX()
{
    return posX;
}

double Planet::getPosY()
{
    return posY;
}

int Planet::getMass()
{
    return mass;
}

Planet::~Planet()
{
}
