#pragma once

#include <queue>
#include <memory>

#include <glad/glad.h>

#include <SDL2/SDL.h>

namespace my {
struct Window {
  SDL_Window *handle;
  std::weak_ptr<Window> parent;
};

using WindowHandle = std::shared_ptr<Window>;

class winit {
public:
  void init();
  void deinit();

  WindowHandle open_window(WindowHandle window_parent = nullptr);
  void close_window(WindowHandle window);

  void update();

private:
  WindowHandle m_window_root;
  std::queue<std::weak_ptr<Window>> m_windows;
  SDL_GLContext m_gl_context;
};
} // namespace my
