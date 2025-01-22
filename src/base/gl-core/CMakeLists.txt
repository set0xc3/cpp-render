project(gl-core)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} assimp::assimp imgui::imgui SDL2::SDL2)
