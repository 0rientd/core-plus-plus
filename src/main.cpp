#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
  SDL_Color color = {255, 255, 255, 255};

  SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect dest = { x, y, surface->w, surface->h };

  SDL_FreeSurface(surface);

  SDL_RenderCopy(renderer, texture, NULL, &dest);

  SDL_DestroyTexture(texture);
}

void drawBaseLine(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderDrawLine(renderer, 100, 100, 300, 100);
}

void drawUsageLine(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_RenderDrawLine(renderer, 100, 100, 200, 100);
}

int main(int argc, char* argv[]) {
  const int FPS = 1;
  const int frameDelay = 1000 / FPS;
  const int default_width = 800;
  const int default_height = 600;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
      
    return 1;
  }

  if (TTF_Init() == -1) {
      std::cerr << "TTF_Init Error: "
                << TTF_GetError() << std::endl;

      SDL_Quit();
      return 1;
  }

  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 12);
  if (!font) {
      std::cerr << "TTF_OpenFont Error: "
                << TTF_GetError() << std::endl;

      TTF_Quit();
      SDL_Quit();

      return 1;
  }

  int width = default_width;
  int height = default_height;

  if (argc >= 3) {
    width = std::atoi(argv[1]);
    height = std::atoi(argv[2]);
  }

  SDL_Window* window = SDL_CreateWindow("Core++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
    Uint32 frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
    
    drawText(renderer, font, "Disk Usage", 100, 80);
    drawBaseLine(renderer);
    drawUsageLine(renderer);

    SDL_RenderPresent(renderer);

    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
