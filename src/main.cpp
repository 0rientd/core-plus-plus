#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
      return 1;
  }

  SDL_Window* window = SDL_CreateWindow("Core++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, std::stoi(argv[1]), std::stoi(argv[2]), SDL_WINDOW_SHOWN);
  if (!window) {
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
      std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
  }

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
