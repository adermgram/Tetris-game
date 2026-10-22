cmake_minimum_required(VERSION 3.17)
project(Tetris CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# raylib 5.0 declares an old cmake_minimum_required that CMake 4+ rejects.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Use an installed raylib if there is one, otherwise download it.
include(FetchContent)
FetchContent_Declare(raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS 5.0)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

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

target_include_directories(tetris PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(tetris PRIVATE raylib)

# Avoid needing the MinGW runtime DLLs next to the exe.
if(MINGW)
    target_link_options(tetris PRIVATE -static)
endif()

# Copy resources next to the executable.
add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:tetris>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sounds $<TARGET_FILE_DIR:tetris>/sounds)

# cmake --build <dir> --target run
add_custom_target(run
    COMMAND tetris
    WORKING_DIRECTORY $<TARGET_FILE_DIR:tetris>
    DEPENDS tetris
    USES_TERMINAL)
