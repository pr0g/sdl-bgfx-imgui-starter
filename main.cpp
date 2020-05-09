#include "SDL.h"
#include "SDL_syswm.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "as/as-math-ops.hpp"
#include "as/as-view.hpp"
#include "camera.hpp"
#include "file-ops.h"
#include "bgfx-imgui/imgui_impl_bgfx.h"
#include "sdl-imgui/imgui_impl_sdl.h"
#include "imgui.h"

#include <iostream>
#include <fstream>

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};

static bgfx::ShaderHandle create_shader(const std::string& shader, const char* name)
{
    const bgfx::Memory* mem = bgfx::copy(shader.data(), shader.size());
    const bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, name);
    return handle;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    } else {
        const int width = 800;
        const int height = 600;
        SDL_Window* window = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN);

         if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            return 1;
        }

        bgfx::PlatformData pd{};
        pd.nwh = wmi.info.win.window;
        bgfx::setPlatformData(pd);

        bgfx::Init bgfxInit;
        bgfxInit.type = bgfx::RendererType::Count; // auto choose renderer
        bgfxInit.resolution.width = width;
        bgfxInit.resolution.height = height;
        bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
        bgfx::init(bgfxInit);

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, width, height);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();

        ImGui_Implbgfx_Init(255);
        ImGui_ImplSDL2_InitForD3D(window);

        bgfx::VertexLayout posColVertLayout;
        posColVertLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
        bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), posColVertLayout);
        bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

        std::string vshader;
        if (!read_file("shader/v_simple.bin", vshader)) {
            return 1;
        }

        bgfx::ShaderHandle vsh = create_shader(vshader, "vshader");

        std::string fshader;
        if (!read_file("shader/f_simple.bin", fshader)) {
            return 1;
        }

        bgfx::ShaderHandle fsh = create_shader(fshader, "fshader");

        bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

        for (bool quit = false; !quit;) {
            int key = 255;
            SDL_Event currentEvent;
            while (SDL_PollEvent(&currentEvent) != 0) {
                ImGui_ImplSDL2_ProcessEvent(&currentEvent);
                if (currentEvent.type == SDL_QUIT) {
                    quit = true;
                    break;
                }

                switch (currentEvent.type) {
                    case SDL_KEYDOWN:
                        int bs = SDLK_BACKSPACE;
                        key = currentEvent.key.keysym.sym;
                        break;
                }
            }

            ImGui_Implbgfx_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();

            // ImGui::ShowDemoWindow();

            ImGui::Text("Hello, world!");
            static char str1[128] = "";
            ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", str1, IM_ARRAYSIZE(str1));

            ImGui::Render();

            camera_t camera{{0.0f, 0.0f, -5.0f}, 0.0f, 0.0f};

            float view[16];
            as::mat::to_arr(camera.view(), view);

            float proj[16];
            as::mat::to_arr(
                as::view::perspective_d3d_lh(as::deg_to_rad(60.0f),
                float(width) / float(height), 0.1f, 100.0f),
                proj);

            bgfx::setViewTransform(0, view, proj);

            as::mat4_t rot = as::mat4::from_mat3(
                as::mat3::rotation_zxy(as::deg_to_rad(45.0f), 0.0f,
                as::deg_to_rad(45.0f)));

            float model[16];
            as::mat::to_arr(rot, model);
            bgfx::setTransform(model);

            bgfx::setVertexBuffer(0, vbh);
            bgfx::setIndexBuffer(ibh);

            bgfx::submit(0, program);

            bgfx::frame();
        }

        ImGui_ImplSDL2_Shutdown();
        ImGui_Implbgfx_Shutdown();

        ImGui::DestroyContext();
        bgfx::shutdown();

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}
