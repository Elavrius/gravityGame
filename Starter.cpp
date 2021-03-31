#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "Utils.h"
#include "Planet.h"
#include "Gravity.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char* args[])
{
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    std::vector<Planet*> planetCollection;
    double deltaTime = 0;
    double last = SDL_GetTicks();
    double current = 0;
    int xMouse, yMouse;

    int state = 0;
    int newPLanetX = 0, newPLanetY = 0;
    int newPLanetRadius = 1;
    int speedLineX = 0, speedLineY = 0;
    bool moveable = true;

    while(true) {
        current = SDL_GetTicks();
        deltaTime = (current - last) / 1000;
        if (deltaTime > 0) {
            last = current;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    break;
                }
                if (state == 0 && event.type == SDL_MOUSEBUTTONDOWN) {
                    moveable = event.button.button == SDL_BUTTON_LEFT;
                    SDL_GetMouseState(&newPLanetX, &newPLanetY);
                    state = 1;
                }
                else if (state == 1) {
                    SDL_GetMouseState(&xMouse, &yMouse);
                    newPLanetRadius = getDistance(newPLanetX, newPLanetY, xMouse, yMouse);
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        SDL_GetMouseState(&speedLineX, &speedLineY);
                        if (newPLanetRadius < 1) {
                            newPLanetRadius = 1;
                        }
                        if (!moveable) {
                            Planet* planet = new Planet(*renderer, newPLanetX, newPLanetY, newPLanetRadius, SCREEN_WIDTH, SCREEN_HEIGHT, moveable);
                            planetCollection.push_back(planet);
                            newPLanetRadius = 0;
                            state = 0;
                            std::cout << "deltaTime: " << deltaTime << " number of planets: " << planetCollection.size()<< "\n";
                        }
                        else {
                            state = 2;
                        }
                    }
                }
                else if (state == 2) {
                    SDL_GetMouseState(&speedLineX, &speedLineY);
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        Planet* planet = new Planet(*renderer, newPLanetX, newPLanetY, newPLanetRadius, SCREEN_WIDTH, SCREEN_HEIGHT, moveable);
                        planet->velocityX = (double)newPLanetX - speedLineX;
                        planet->velocityY = (double)newPLanetY - speedLineY;
                        planetCollection.push_back(planet);
                        newPLanetRadius = 0;
                        state = 0;
                        std::cout << "deltaTime: " << deltaTime << " number of planets: " << planetCollection.size() << "\n";
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            if (state == 1 || state == 2) {
                drawCircle(renderer, newPLanetX, newPLanetY, newPLanetRadius);
                if (state == 2) {
                    SDL_RenderDrawLine(renderer, newPLanetX, newPLanetY, speedLineX, speedLineY);
                }
            }

            if (planetCollection.size() > 0) {
                for (auto planet : planetCollection) {
                    planet->draw();
                }

                for (int i = 0; i < planetCollection.size() - 1; i++) {
                    for (int j = i + 1; j < planetCollection.size(); j++) {
                        Gravity::applyGravity(*planetCollection[i], *planetCollection[j], deltaTime);
                    }
                }
                for (auto planet : planetCollection) {
                    planet->move(deltaTime);
                }
            }

            SDL_RenderPresent(renderer);
        }
    }
    for (auto p : planetCollection)
    {
        delete p;
    }
    planetCollection.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Clean" << std::endl;
    return 0;
}