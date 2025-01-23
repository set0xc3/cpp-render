#include "winit.hpp"

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
  m_window_root = open_window();

  m_gl_context = SDL_GL_CreateContext(m_window_root->handle);

  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  std::cout << glGetString(GL_VERSION) << std::endl;
}

WindowHandle winit::open_window(WindowHandle window_parent) {
  auto ret = std::make_shared<Window>();

  ret->handle =
      SDL_CreateWindow("gl-core", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_OPENGL);

  if (!ret->handle) {
    const std::string err = SDL_GetError();
    throw std::runtime_error("Cannot create window SDL: " + err);
    return nullptr;
  }

  m_windows.push(ret);

  return ret;
}

void winit::deinit() { SDL_Quit(); }

void winit::close_window(WindowHandle window) {
  SDL_DestroyWindow(window->handle);
}

void winit::update() {}
} // namespace my
