#include "SDL.h"
#include "SDL_syswm.h"
#include "bgfx-imgui/imgui_impl_bgfx.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "bx/math.h"
#include "file-ops.h"
#include "imgui.h"
#include "sdl-imgui/imgui_impl_sdl.h"

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cube_vertices[] = {
    {-1.0f, 1.0f, 1.0f, 0xff000000},   {1.0f, 1.0f, 1.0f, 0xff0000ff},
    {-1.0f, -1.0f, 1.0f, 0xff00ff00},  {1.0f, -1.0f, 1.0f, 0xff00ffff},
    {-1.0f, 1.0f, -1.0f, 0xffff0000},  {1.0f, 1.0f, -1.0f, 0xffff00ff},
    {-1.0f, -1.0f, -1.0f, 0xffffff00}, {1.0f, -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t cube_tri_list[] = {
    0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
    1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
};

static bgfx::ShaderHandle createShader(
    const std::string& shader, const char* name)
{
    const bgfx::Memory* mem = bgfx::copy(shader.data(), shader.size());
    const bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, name);
    return handle;
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    } else {
        const int width = 800;
        const int height = 600;
        SDL_Window* window = SDL_CreateWindow(
            argv[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
            height, SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            printf(
                "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            return 1;
        }

        bgfx::renderFrame(); // single threaded mode

        bgfx::PlatformData pd{};
#if BX_PLATFORM_WINDOWS
        pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
        pd.nwh = wmi.info.cocoa.window;
#endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX

        bgfx::Init bgfx_init;
        bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
        bgfx_init.resolution.width = width;
        bgfx_init.resolution.height = height;
        bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
        bgfx_init.platformData = pd;
        bgfx::init(bgfx_init);

        bgfx::setViewClear(
            0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDFF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, width, height);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_Implbgfx_Init(255);
#if BX_PLATFORM_WINDOWS
        ImGui_ImplSDL2_InitForD3D(window);
#elif BX_PLATFORM_OSX
        ImGui_ImplSDL2_InitForMetal(window);
#endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX

        bgfx::VertexLayout pos_col_vert_layout;
        pos_col_vert_layout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
        bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
            bgfx::makeRef(cube_vertices, sizeof(cube_vertices)),
            pos_col_vert_layout);
        bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
            bgfx::makeRef(cube_tri_list, sizeof(cube_tri_list)));

        std::string vshader;
        if (!fileops::read_file("shader/v_simple.bin", vshader)) {
            return 1;
        }

        std::string fshader;
        if (!fileops::read_file("shader/f_simple.bin", fshader)) {
            return 1;
        }

        bgfx::ShaderHandle vsh = createShader(vshader, "vshader");
        bgfx::ShaderHandle fsh = createShader(fshader, "fshader");

        bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

        float cam_pitch = 0.0f;
        float cam_yaw = 0.0f;
        float rot_scale = 0.01f;

        int prev_mouse_x = 0;
        int prev_mouse_y = 0;

        for (bool quit = false; !quit;) {
            SDL_Event currentEvent;
            while (SDL_PollEvent(&currentEvent) != 0) {
                ImGui_ImplSDL2_ProcessEvent(&currentEvent);
                if (currentEvent.type == SDL_QUIT) {
                    quit = true;
                    break;
                }
            }

            ImGui_Implbgfx_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);

            ImGui::NewFrame();
            ImGui::ShowDemoWindow(); // your drawing here
            ImGui::Render();

            // simple input code for orbit camera
            int mouse_x, mouse_y;
            const int buttons = SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
            if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0) {
                int delta_x = mouse_x - prev_mouse_x;
                int delta_y = mouse_y - prev_mouse_y;

                cam_yaw += float(-delta_x) * rot_scale;
                cam_pitch += float(-delta_y) * rot_scale;
            }

            prev_mouse_x = mouse_x;
            prev_mouse_y = mouse_y;

            float cam_rotation[16];
            bx::mtxRotateXYZ(cam_rotation, cam_pitch, cam_yaw, 0.0f);

            float cam_translation[16];
            bx::mtxTranslate(cam_translation, 0.0f, 0.0f, -5.0f);

            float cam_transform[16];
            bx::mtxMul(cam_transform, cam_translation, cam_rotation);

            float view[16];
            bx::mtxInverse(view, cam_transform);

            float proj[16];
            bx::mtxProj(
                proj, 60.0f, float(width) / float(height), 0.1f, 100.0f,
                bgfx::getCaps()->homogeneousDepth);

            bgfx::setViewTransform(0, view, proj);

            float model[16];
            bx::mtxIdentity(model);
            bgfx::setTransform(model);

            bgfx::setVertexBuffer(0, vbh);
            bgfx::setIndexBuffer(ibh);

            bgfx::submit(0, program);

            bgfx::frame();
        }

        bgfx::destroy(vbh);
        bgfx::destroy(ibh);
        bgfx::destroy(program);

        ImGui_ImplSDL2_Shutdown();
        ImGui_Implbgfx_Shutdown();

        ImGui::DestroyContext();
        bgfx::shutdown();

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}
