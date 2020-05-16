cmake_minimum_required(VERSION 3.15)
project(sdl-bgfx-imgui-starter LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(bgfx REQUIRED)
find_package(imgui REQUIRED)

include(FetchContent)

FetchContent_Declare(
    as-camera GIT_REPOSITORY https://github.com/pr0g/as-camera.git
)

FetchContent_MakeAvailable(as-camera)

add_executable(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME} PRIVATE
    main.cpp
    sdl-imgui/imgui_impl_sdl.cpp
    bgfx-imgui/imgui_impl_bgfx.cpp
    sdl-as-camera/sdl-as-camera.cpp
)

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE -DAS_PRECISION_FLOAT -DAS_COL_MAJOR
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    bgfx::bgfx
    imgui::imgui
    as-camera
)

if (WIN32)
# copy the .dll file to the same folder as the executable
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
