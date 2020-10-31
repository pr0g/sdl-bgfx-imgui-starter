cmake_minimum_required(VERSION 3.15)

project(third-party)

include(ExternalProject)

ExternalProject_Add(
    SDL2 
    URL https://www.libsdl.org/release/SDL2-2.0.12.tar.gz
    URL_HASH MD5=783b6f2df8ff02b19bb5ce492b99c8ff
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SDL2/build/${CMAKE_BUILD_TYPE}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

ExternalProject_Add(
    bgfx
    GIT_REPOSITORY https://github.com/pr0g/bgfx.cmake.git
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bgfx/build/${CMAKE_BUILD_TYPE}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

ExternalProject_Add(
    cmakefied
    GIT_REPOSITORY https://github.com/pr0g/cmakefied.git
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CONFIGURE_COMMAND <SOURCE_DIR>/git-clone.sh imgui COMMAND cmake -S <DOWNLOAD_DIR>/imgui -B build/${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    BUILD_COMMAND cmake --build <BINARY_DIR>/build/${CMAKE_BUILD_TYPE}
    INSTALL_COMMAND cmake --install <BINARY_DIR>/build/${CMAKE_BUILD_TYPE})
