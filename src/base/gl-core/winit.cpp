#include "winit.hpp"

#include <SDL_video.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <ranges>
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

  m_window_root = open_window("gl-core");

  auto window_handle = SDL_GetWindowFromID(m_window_root->id);
  SDL_GL_MakeCurrent(window_handle, m_window_root->gl_context);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
  std::cout << glGetString(GL_VERSION) << std::endl;
}

Window winit::open_window(const std::string &title, Window window_parent) {
  auto ret = std::make_shared<WindowInfo>();

  SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
  auto window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_OPENGL);
  SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);

  if (!window) {
    const std::string err = SDL_GetError();
    throw std::runtime_error("Cannot create window SDL: " + err);
  }

  ret->id = SDL_GetWindowID(window);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context) {
    SDL_DestroyWindow(window);
    const std::string err = SDL_GetError();
    throw std::runtime_error("Cannot create OpenGL context: " + err);
  }
  ret->gl_context = context;

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

  // 1. Собираем детей в отдельный вектор перед обработкой
  std::vector<Window> children;
  for (auto &[id, weak_child] : window->children) {
    if (auto child = weak_child.lock()) {
      children.push_back(child);
    }
  }

  // 2. Рекурсивно закрываем детей во время итерации
  for (auto &child : children) {
    close_window(child);
  }

  // 3. Удаляем связь с родителем
  if (auto parent = window->parent.lock()) {
    parent->children.erase(window->id);
  }

  // 4. Освобождаем ресурсы в правильном порядке
  if (window->gl_context) {
    SDL_GL_DeleteContext(window->gl_context);
    window->gl_context = nullptr;
  }

  if (SDL_Window *sdl_window = SDL_GetWindowFromID(window->id)) {
    SDL_DestroyWindow(sdl_window);
  }

  // 6. Удаляем из общего списка окон
  m_windows.erase(window->id);
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
          auto it = m_windows.find(window_id);
          if (it != m_windows.end()) {
            close_window(it->second);
          }
          if (m_windows.empty()) {
            quit = true;
          }
        }
        break;
      default:
        break;
      }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
  }
}
} // namespace my
