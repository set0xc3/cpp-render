project(gl-core)

add_executable(${PROJECT_NAME} main.cpp winit.hpp winit.cpp)

target_link_libraries(${PROJECT_NAME} assimp::assimp imgui::imgui SDL2::SDL2 glad)
