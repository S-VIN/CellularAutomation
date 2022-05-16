cmake_minimum_required(VERSION 3.21)
project(cellularAutomaton)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


add_executable(cellularAutomaton main.cpp Automation.h Painter.h Field.h SettingsStore.h Graphic.h)

target_link_libraries(cellularAutomaton sfml-graphics sfml-window sfml-system ${wxWidgets_LIBRARIES})