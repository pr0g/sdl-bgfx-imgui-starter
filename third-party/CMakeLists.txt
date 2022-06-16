cmake_minimum_required(VERSION 3.15)

project(third-party)

include(ExternalProject)

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (NOT isMultiConfig)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "" FORCE)
  endif ()
  set(build_type_dir ${CMAKE_BUILD_TYPE})
  set(build_type_arg -DCMAKE_BUILD_TYPE=$<CONFIG>)
else ()
  set(build_config_arg --config=$<CONFIG>)
endif ()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  set(THIRD_PARTY_CMAKE_COMMAND emcmake cmake)
else ()
  set(THIRD_PARTY_CMAKE_COMMAND ${CMAKE_COMMAND})
endif ()

ExternalProject_Add(
  SDL2
  URL https://www.libsdl.org/release/SDL2-2.0.22.tar.gz
  URL_HASH MD5=40aedb499cb2b6f106d909d9d97f869a
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SDL2/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
  INSTALL_COMMAND cmake --build <BINARY_DIR> --target install ${build_config_arg})

ExternalProject_Add(
  bgfx
  GIT_REPOSITORY https://github.com/pr0g/bgfx.cmake.git
  GIT_TAG 424b711f35b2d795872fc072624b13fa1183b832
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bgfx/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
             "$<$<PLATFORM_ID:Emscripten>:-DBGFX_CONFIG_MULTITHREADED=OFF>"
             -DBGFX_BUILD_EXAMPLES=OFF
  BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
  INSTALL_COMMAND cmake --build <BINARY_DIR> --target install ${build_config_arg})

ExternalProject_Add(
  imgui.cmake
  GIT_REPOSITORY https://github.com/pr0g/imgui.cmake.git
  GIT_TAG 7e417a39d496820cc25cacbf28b544796a81a634
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/imgui/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
             -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=ON
  BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
  INSTALL_COMMAND cmake --build <BINARY_DIR> --target install ${build_config_arg})
