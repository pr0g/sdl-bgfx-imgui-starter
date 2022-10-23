cmake_minimum_required(VERSION 3.24)

if (NOT SUPERBUILD)
  project(third-party)
endif ()

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

if (SUPERBUILD)
  set(PREFIX_DIR
      ${CMAKE_CURRENT_SOURCE_DIR}/third-party/${THIRD_PARTY_BUILD_DIR_NAME})
else ()
  set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif ()

if (NOT EMSCRIPTEN)
  ExternalProject_Add(
    SDL2
    URL https://github.com/libsdl-org/SDL/releases/download/release-2.24.1/SDL2-2.24.1.tar.gz
    URL_HASH MD5=10bad2a286f155565edc611f41345de1
    PREFIX ${PREFIX_DIR}
    BINARY_DIR ${PREFIX_DIR}/src/SDL2-build/${build_type_dir}
    CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
    CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
    INSTALL_COMMAND cmake --build <BINARY_DIR> --target install
                    ${build_config_arg})
endif ()

ExternalProject_Add(
  bgfx
  GIT_REPOSITORY https://github.com/pr0g/bgfx.cmake.git
  GIT_TAG 26a0f1e54d131841dab511539ff3e6c5e6472fed
  PREFIX ${PREFIX_DIR}
  BINARY_DIR ${PREFIX_DIR}/src/bgfx-build/${build_type_dir}
  CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
  CMAKE_ARGS ${build_type_arg}
             -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
             "$<$<PLATFORM_ID:Emscripten>:-DBGFX_CONFIG_MULTITHREADED=OFF>"
             -DBGFX_BUILD_EXAMPLES=OFF
  BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
  INSTALL_COMMAND cmake --build <BINARY_DIR> --target install
                  ${build_config_arg})

ExternalProject_Add(
  imgui.cmake
  GIT_REPOSITORY https://github.com/pr0g/imgui.cmake.git
  GIT_TAG 7e417a39d496820cc25cacbf28b544796a81a634
  PREFIX ${PREFIX_DIR}
  BINARY_DIR ${PREFIX_DIR}/src/imgui.cmake-build/${build_type_dir}
  CMAKE_COMMAND ${THIRD_PARTY_CMAKE_COMMAND}
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
             -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=ON
  BUILD_COMMAND cmake --build <BINARY_DIR> ${build_config_arg}
  INSTALL_COMMAND cmake --build <BINARY_DIR> --target install
                  ${build_config_arg})
