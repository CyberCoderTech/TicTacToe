cmake_minimum_required(VERSION 3.20)

project(TicTacToc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE
    src/main.cpp
    src/ResourceManager.cpp
    src/state/GameModeState.cpp
    src/state/GameState.cpp
    src/state/MenuState.cpp
    src/state/StateManager.cpp
    src/mvc/AIController.cpp
    src/mvc/BoardModel.cpp
    src/mvc/BoardView.cpp
    src/mvc/PlayerController.cpp
    src/ui/Button.cpp)

find_package(SFML 2.6.2 CONFIG COMPONENTS REQUIRED window system graphics)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system)

configure_file(
    ${CMAKE_SOURCE_DIR}/assets/fonts/Roboto-Black.ttf
    ${CMAKE_BINARY_DIR}/Roboto-Black.ttf
    COPYONLY
)

# --- SEKCJA TESTÓW JEDNOSTKOWYCH ---
enable_testing()
find_package(Catch2 REQUIRED)

add_executable(unit_tests 
    tests/test_board.cpp
    src/mvc/BoardModel.cpp
)


target_include_directories(unit_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
add_test(NAME BoardModelTest COMMAND unit_tests)
