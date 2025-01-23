#include <iostream>

#include "winit.hpp"

int main(int argc, char *argv[]) {
  auto winit = std::make_unique<my::winit>();
  winit->init();
  winit->update();
  return 0;
}
