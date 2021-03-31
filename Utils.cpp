#include "Utils.h"
#include <math.h>

double getDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow((double)x2 - x1, 2) + pow((double)y2 - y1, 2));
}

void drawCircle(SDL_Renderer * renderer, int posX, int posY, int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, posX + x, posY - y);
        SDL_RenderDrawPoint(renderer, posX + x, posY + y);
        SDL_RenderDrawPoint(renderer, posX - x, posY - y);
        SDL_RenderDrawPoint(renderer, posX - x, posY + y);
        SDL_RenderDrawPoint(renderer, posX + y, posY - x);
        SDL_RenderDrawPoint(renderer, posX + y, posY + x);
        SDL_RenderDrawPoint(renderer, posX - y, posY - x);
        SDL_RenderDrawPoint(renderer, posX - y, posY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
