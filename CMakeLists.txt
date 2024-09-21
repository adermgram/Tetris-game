cmake_minimum_required(VERSION 3.17)
project(Tetris)

include(FetchContent)
FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(raylib)

find_package(raylib 2.0 REQUIRED)

add_executable(tetris
    src/main.cpp
    src/game.cpp
    src/ball.cpp
    src/block.cpp
    src/colors.cpp
    src/grid.cpp
    src/position.cpp
    src/tetris.cpp
)
target_include_directories(tetris
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/)

target_link_libraries(tetris raylib)

# Copy resources
add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/fonts
    $<TARGET_FILE_DIR:tetris>/fonts)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/sounds
    $<TARGET_FILE_DIR:tetris>/sounds)