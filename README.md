## cpp-render

## Требования

- **Стандарт языка:** C++20.
- **Компилятор:** Clang.
- **Система сборки:** CMake + Ninja.
- **Графический рендер:** OpenGL Core, DirectX11, DirectX12, Vulkan.

## Зависимости

- Clang 19.1.6.
- CMake 3.31.3.
- Ninja 1.12.1.
- Boost 1.86.0.
- SDL2 2.30.11.
- Assimp 5.4.3.
- ImGui 1.91.4.

## Собрать

`cmake -B build -G Ninja && cmake --build build --parallel $(nproc)`
