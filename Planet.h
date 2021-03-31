#pragma once
#include <SDL_render.h>
class Planet
{
public:
	Planet(SDL_Renderer & renderer, double posX, double posY, int radius, int screenWidth, int screenHeight, bool mobeable);
	int radius;
	double velocityX;
	double velocityY;
	void move(double delatTime);
	void draw();
	double getPosX();
	double getPosY();
	int getMass();
	~Planet();

private:
	bool moveable;
	int UPPER_BORDER;
	int BOTTOM_BORDER;
	int LEFT_BORDER;
	int RIGHT_BORDER;
	SDL_Renderer * renderer;
	double posX;
	double posY;
	int mass;
};