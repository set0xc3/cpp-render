#include <iostream>
#include <memory>
#include <stop_token>

#include "winit.hpp"

int main(int argc, char *argv[]) {
  std::unique_ptr<my::winit> winit = std::make_unique<my::winit>();

  winit->init();

  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
        break;
      default:
        break;
      }
    }

    // ...

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
  }

  // Автоматическое освобождение ресурсов происходит благодаря умным указателям
  SDL_Quit();

  return 0;
}
