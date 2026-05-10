cmake_minimum_required(VERSION 3.20)

project(TicTacToc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(SOURCE
    src/main.cpp)

find_package(SFML 2.6.2 CONFIG COMPONENTS REQUIRED window system graphics)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system)