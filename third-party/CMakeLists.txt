cmake_minimum_required(VERSION 3.15)

project(third-party)

include(ExternalProject)

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (NOT isMultiConfig)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
    endif()
    set(build_type_dir ${CMAKE_BUILD_TYPE})
    set(build_type_arg -DCMAKE_BUILD_TYPE=$<CONFIG>)
endif()

ExternalProject_Add(
    SDL2
    URL https://www.libsdl.org/tmp/SDL-2.0.13-14202.tar.gz
    URL_HASH MD5=f10328dc1724470433e3ca05a662d146
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SDL2/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

ExternalProject_Add(
    bgfx
    GIT_REPOSITORY https://github.com/pr0g/bgfx.cmake.git
    GIT_TAG        origin/main
    GIT_SHALLOW    1
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bgfx/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D BGFX_BUILD_EXAMPLES=OFF)

ExternalProject_Add(
    cmakefied
    GIT_REPOSITORY https://github.com/pr0g/cmakefied.git
    GIT_TAG        origin/main
    UPDATE_COMMAND bash <SOURCE_DIR>/git-clone.sh imgui
    SOURCE_SUBDIR ../imgui
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/imgui/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
