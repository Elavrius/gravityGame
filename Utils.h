#pragma once
#include <SDL_render.h>

double getDistance(int x1, int y1, int x2, int y2);

void drawCircle(SDL_Renderer* renderer, int posX, int posY, int radius);