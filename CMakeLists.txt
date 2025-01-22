cmake_minimum_required(VERSION 3.14)
project(test)

# Установите политику CMP0167, чтобы избежать предупреждения
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Укажите, хотите ли вы использовать статические или динамические библиотеки
#set(Boost_USE_STATIC_LIBS ON)  # Использовать статические библиотеки

# Найдите пакет Boost с нужными компонентами
#find_package(Boost 1.87 REQUIRED COMPONENTS thread)

# Проверьте, найдены ли необходимые компоненты
# if(Boost_FOUND)
#   message(STATUS "Found Boost version ${Boost_VERSION}")
#   message(STATUS "Using Boost components: ${Boost_FIND_COMPONENTS}")
# else()
#   message(FATAL_ERROR "Boost not found!")
# endif()

add_subdirectory(src)

# Подключите найденные библиотеки Boost к вашему проекту
#target_link_libraries(test Boost::thread)
