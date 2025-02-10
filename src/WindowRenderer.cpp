#include <WindowRenderer.hpp>

SDL_Renderer* RenderWindow::renderer = nullptr;

RenderWindow::RenderWindow(const char* title, int width, int height){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){ std::cerr << "Couldn't create window" << std::endl; }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){ std::cerr << "Couldn't create renderer" << std::endl; }
}

void RenderWindow::present(){
    SDL_RenderPresent(renderer);
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::cout << "Winow and renderer succesfully destroyed." << std::endl;
}

SDL_Renderer* RenderWindow::getRenderer(){
    return renderer;
}