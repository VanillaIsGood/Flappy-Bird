#pragma once
#include <SDL.h>
#include <iostream>

class RenderWindow{
public:
    RenderWindow(const char* title, int width, int height);

    void present();
    void clear();
    void clean();
    static SDL_Renderer* getRenderer();
private:
    SDL_Window* window;
    static SDL_Renderer* renderer;
};