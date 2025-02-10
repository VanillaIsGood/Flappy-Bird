#include <SDL_image.h>
#include <Texture_generator.hpp>
#include <iostream>


SDL_Texture *generate_texture::load_texture(const char *filepath) {
  SDL_Renderer *renderer = RenderWindow::getRenderer();
  if (!renderer) {
    std::cerr << "Renderer not initialized.\n";
    return nullptr;
  }

  SDL_Surface *surface = IMG_Load(filepath);
  if (!surface) {
    std::cerr << "Could not load surface from " << filepath << ": "
              << IMG_GetError() << '\n';
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    std::cerr << "Could not create texture from " << filepath << ": "
              << SDL_GetError() << '\n';
  }
  return texture;
}

void generate_texture::render(SDL_Texture *texture, int x, int y, int w,
                              int h) {
  if (!texture) {
    std::cerr << "Invalid texture provided for rendering.\n";
    return;
  }

  SDL_Renderer *renderer = RenderWindow::getRenderer();
  if (!renderer) {
    std::cerr << "Renderer not initialized.\n";
    return;
  }

  SDL_Rect dest = {x, y, w, h};
  if (SDL_RenderCopy(renderer, texture, nullptr, &dest) != 0) {
    std::cerr << "Failed to render texture: " << SDL_GetError() << '\n';
  }
}

SDL_Rect &generate_texture::getRect() { return dest; }
