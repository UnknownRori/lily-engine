#include <raylib.h>
#include "lily/engine.h"
#include "lily/memory.h"
#include "lily/types.h"

#include "./ini/engine_config.h"
#include "./scene_manager.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static bool lily_should_exit();
static void lily_update();

rori_status_t lily_engine_init_impl(lily_engine_param params)
{
    char* title = params.title;
    u32  width  = params.width;
    u32  height = params.height;
    u8   fps    = params.fps;
    bool vsync  = params.vsync;
    bool read_config = false;
    if (title == NULL) {
        title = "Lily Engine by UnknownRori";
    }

    if (params.read_engine_ini) {
        read_config = !engine_ini_parse(&title, &width, &height, &fps, &vsync);
    }

    InitAudioDevice();
    InitWindow(width, height, title);
    SetTargetFPS(fps);

    if (vsync) {
        SetWindowState(FLAG_VSYNC_HINT);
    }

    scene_manager_init();
    scene_manager_change(params.start);

    if (read_config) {
        RORI_FREE(title);
    }

    return RORI_SUCCESS;
}

rori_status_t lily_engine_run()
{
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(lily_update, 0, 1);
#else
    while (!WindowShouldClose()) {
        if (lily_should_exit()) break;
        lily_update();
    }
#endif

    return RORI_SUCCESS;
}

///////////////////////////////////////////////////////

static bool lily_should_exit()
{
    return false;
}

static void lily_update()
{
    scene_manager_update();
    BeginDrawing(); {
        scene_manager_render();
    } EndDrawing();
}
