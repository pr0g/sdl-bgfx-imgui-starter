#include "sdl-as-camera.h"

#include "as-camera/as-camera-controller.hpp"
#include "bitfield-enum-class/bitfield-enum-class.hpp"
#include "SDL.h"

asc::MotionType motionFromKey(int key)
{
    switch (key) {
        case SDL_SCANCODE_W:
            return asc::MotionType::Forward;
        case SDL_SCANCODE_S:
            return asc::MotionType::Backward;
        case SDL_SCANCODE_A:
            return asc::MotionType::Left;
        case SDL_SCANCODE_D:
            return asc::MotionType::Right;
        case SDL_SCANCODE_Q:
            return asc::MotionType::Down;
        case SDL_SCANCODE_E:
            return asc::MotionType::Up;
        default:
            return asc::MotionType::None;
    }
}

void updateCameraControlKeyboardSdl(
    const SDL_Event& event, asc::CameraControl& control)
{
    using bec::operator^=;
    using bec::operator|=;

    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            const int key = event.key.keysym.scancode;
            if (event.type == SDL_KEYDOWN) {
                control.motion |= motionFromKey(key);
            }
            if (event.type == SDL_KEYUP) {
                control.motion ^= motionFromKey(key);
            }
        } break;
        case SDL_MOUSEWHEEL:
            control.delta_dolly = event.wheel.y;
            break;
        default:
            break;
    }
}

MouseState mouseState()
{
    using bec::operator|=;

    MouseState mouse_state{};
    const int buttons =
        SDL_GetGlobalMouseState(&mouse_state.xy[0], &mouse_state.xy[1]);
    mouse_state.buttons |= ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
                               ? MouseButtons::Lmb
                               : MouseButtons::None;
    mouse_state.buttons |= ((buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0)
                               ? MouseButtons::Rmb
                               : MouseButtons::None;
    mouse_state.buttons |= ((buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0)
                               ? MouseButtons::Mmb
                               : MouseButtons::None;
    return mouse_state;
}

void updateCameraControlMouseSdl(
    asc::CameraControl& control, const asc::CameraProperties& props,
    MouseState& prev_mouse_state)
{
    const MouseState mouse_state = mouseState();

    using bec::operator&;
    if ((mouse_state.buttons & MouseButtons::Rmb) == MouseButtons::Rmb) {
        const as::vec2i_t delta = mouse_state.xy - prev_mouse_state.xy;
        control.delta_pitch = float(delta[1]);
        control.delta_yaw = float(delta[0]);
    }

    prev_mouse_state = mouse_state;
}
