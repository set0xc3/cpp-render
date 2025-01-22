#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <imgui.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

bool quit;
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("gl-core", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);

  while (!quit) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT: {
      quit = true;
      break;
    }

    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
      }
      break;
    }

      SDL_Delay(1);
      return 0;
    }
  }

  SDL_Quit();
}
