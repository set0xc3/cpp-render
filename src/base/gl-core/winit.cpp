#include "winit.hpp"

#include <SDL_video.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stop_token>

namespace my {
void winit::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    const std::string err = SDL_GetError();
    throw std::runtime_error("Failed to initialize SDL: " + err);
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

  // NOTE: Предварительное создание окна для того чтобы инициализировать OpenGL.
  m_window_root = open_window("gl-core");

  auto window_handle = SDL_GetWindowFromID(m_window_root->id);
  m_gl_context = SDL_GL_CreateContext(window_handle);

  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  std::cout << glGetString(GL_VERSION) << std::endl;
}

Window winit::open_window(const std::string &title, Window window_parent) {
  auto ret = std::make_shared<WindowInfo>();

  auto window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_OPENGL);

  if (!window) {
    const std::string err = SDL_GetError();
    throw std::runtime_error("Cannot create window SDL: " + err);
    return nullptr;
  }

  ret->id = SDL_GetWindowID(window);

  if (window_parent) {
    ret->parent = window_parent;
    window_parent->children[ret->id] = ret;
  }

  m_windows[ret->id] = ret;

  return ret;
}

void winit::deinit() { SDL_Quit(); }

void winit::close_window(Window window) {
  if (!window) {
    return;
  }

  auto window_handle = SDL_GetWindowFromID(window->id);
  SDL_DestroyWindow(window_handle);
  m_windows.erase(window->id);

  for (auto &child : window->children) {
    if (window->parent.lock()) {
      window->parent.lock()->children.erase(window->id);
      window->parent.reset();
    }

    close_window(child.second.lock());
  }
}

Window winit::get_window_root() { return m_window_root; }

void winit::update() {
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
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          uint32_t window_id = event.window.windowID;
          close_window(m_windows[window_id].lock());

          if (m_windows.size() == 0) {
            quit = true;
          }
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

  SDL_Quit();
}
} // namespace my
