cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(gui
  gui.cpp
  window.cpp
  window.hpp
)
qt5_use_modules(gui Core Widgets)
target_link_libraries(gui qtmosquitto)
