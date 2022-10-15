include(third-party/CMakeLists.txt)

ExternalProject_Add(
  sdl-bgfx-imgui-starter_superbuild
  DEPENDS SDL2 bgfx imgui.cmake
  SOURCE_DIR ${PROJECT_SOURCE_DIR}
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DSUPERBUILD=OFF
  INSTALL_COMMAND "")