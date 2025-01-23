#pragma once

#include <map>
#include <memory>
#include <queue>
#include <iostream>

#include <glad/glad.h>

#include <SDL2/SDL.h>

namespace my {
struct WindowInfo {
  uint32_t id;
  std::weak_ptr<WindowInfo> parent;
  std::map<uint32_t, std::weak_ptr<WindowInfo>> children;
};

using Window = std::shared_ptr<WindowInfo>;

class winit {
public:
  void init();
  void deinit();

  Window open_window(const std::string &title, Window window_parent = nullptr);
  void close_window(Window window);
  Window get_window_root();

  void update();

private:
  Window m_window_root;
  std::map<uint32_t, std::weak_ptr<WindowInfo>> m_windows;
  SDL_GLContext m_gl_context;
};
} // namespace my
