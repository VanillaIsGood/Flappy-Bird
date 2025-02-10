#pragma once
#include "WindowRenderer.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <iostream>

class generate_texture {
public:
  static SDL_Texture *load_texture(const char *filepath);

  void render(SDL_Texture *texture, int x = 0, int y = 0, int w = 50,
              int h = 50);
              
  SDL_Rect &getRect();

private:
  SDL_Rect dest;
};
