#pragma once

#include "as-camera/as-camera-controller.hpp"
#include "as/as-vec.hpp"
#include "bitfield-enum-class/bitfield-enum-class.hpp"

union SDL_Event;

enum class MouseButtons : uint8_t {
    None = 0,
    Lmb = 1 << 0,
    Rmb = 1 << 1,
    Mmb = 1 << 2
};

template<>
struct bec::EnableBitMaskOperators<MouseButtons>
{
    static const bool enable = true;
};

struct MouseState
{
    as::vec2i_t xy;
    MouseButtons buttons;
};

MouseState mouseState();
asc::MotionType motionFromKey(int key);
void updateCameraControlKeyboardSdl(
    const SDL_Event& event, asc::CameraControl& control);
void updateCameraControlMouseSdl(
    asc::CameraControl& control, const asc::CameraProperties& props,
    MouseState& prev_mouse_state);
