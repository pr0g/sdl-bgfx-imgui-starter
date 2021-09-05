cmake_minimum_required(VERSION 3.15)

project(sdl-bgfx-imgui-starter LANGUAGES CXX)

find_package(SDL2 REQUIRED CONFIG CMAKE_FIND_ROOT_PATH_BOTH)
find_package(bgfx REQUIRED CONFIG CMAKE_FIND_ROOT_PATH_BOTH)
find_package(imgui REQUIRED CONFIG CMAKE_FIND_ROOT_PATH_BOTH)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp sdl-imgui/imgui_impl_sdl.cpp
                                       bgfx-imgui/imgui_impl_bgfx.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static SDL2::SDL2main
                                              bgfx::bgfx bgfx::bx imgui::imgui)
target_link_options(
  ${PROJECT_NAME}
  PRIVATE
  $<$<BOOL:${EMSCRIPTEN}>:-sMAX_WEBGL_VERSION=2
  -sFETCH=1
  -sALLOW_MEMORY_GROWTH=1
  --preload-file=v_simple.bin
  --preload-file=f_simple.bin>)

if (${EMSCRIPTEN})
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_SOURCE_DIR}/shader/v_simple.bin
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_SOURCE_DIR}/shader/f_simple.bin
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif ()

set_target_properties(
  ${PROJECT_NAME}
  # required for project when using visual studio generator
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if (WIN32)
  # copy the SDL2.dll to the same folder as the executable
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif ()
