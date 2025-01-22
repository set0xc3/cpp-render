## cpp-render

## Требования

- **Язык программирования:** C++17.
- **Компилятор:** Clang.
- **Система сборки:** CMake + Ninja.
- **Графический рендер:** OpenGL Core, DirectX11, DirectX12, Vulkan.

## Зависимости

- Boost.

## TODO:

- [ ] Многопоточность.
- [ ] Модульность.
- [ ] Кроссплатформенный рендеринг.
- [ ] Переход на C++20.


## NOTE:
- `cmake -B build -G Ninja && cmake --build build --parallel $(nproc)`
