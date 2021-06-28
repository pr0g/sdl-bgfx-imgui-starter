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
    URL https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
    URL_HASH MD5=76ed4e6da9c07bd168b2acd9bfefab1b
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SDL2/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

ExternalProject_Add(
    bgfx
    GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
    GIT_TAG        4fbe36bace5c92ea314377001f6e7d7fd40819f2
    GIT_SHALLOW    1
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bgfx/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
               -D BGFX_BUILD_EXAMPLES=OFF)

ExternalProject_Add(
    cmakefied
    GIT_REPOSITORY https://github.com/pr0g/cmakefied.git
    GIT_TAG        5b201e9be3fa85fdd987110c4a9a2f91f28c0af1
    UPDATE_COMMAND bash <SOURCE_DIR>/git-clone.sh imgui
    SOURCE_SUBDIR ../imgui
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/imgui/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D IMGUI_DISABLE_OBSOLETE_FUNCTIONS=ON)