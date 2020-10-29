cmake_minimum_required(VERSION 3.15)

project(third-party)

include(ExternalProject)

ExternalProject_Add(
    SDL2 
    URL https://www.libsdl.org/release/SDL2-2.0.12.tar.gz
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

ExternalProject_Add(
    bgfx
    GIT_REPOSITORY https://github.com/pr0g/bgfx.cmake.git
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
    
ExternalProject_Add(
    cmakefied
    GIT_REPOSITORY https://github.com/pr0g/cmakefied.git
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CONFIGURE_COMMAND <SOURCE_DIR>/git-clone.sh imgui COMMAND cmake -S <DOWNLOAD_DIR>/imgui -B build -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    BUILD_COMMAND cmake --build <BINARY_DIR>/build
    INSTALL_COMMAND cmake --install <BINARY_DIR>/build)
