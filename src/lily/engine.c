#include <raylib.h>
#include "lily/engine.h"
#include "lily/memory.h"
#include "lily/config.h"
#include "lily/types.h"

#include "./assets.h"
#include "./config.h"
#include "./scene_manager.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static bool lily_should_exit();
static void lily_update();

rori_status_t lily_engine_init_impl(lily_engine_param params)
{
    if (!engine_ini_parse()) {
        TraceLog(LOG_WARNING, "Configuration load failed");
    }
    const char* title = lily_config_get_cstr("Display", "Title", "Lily Engine by UnknownRori");
    u32  width  = lily_config_get_i32("Display", "Width", 800);
    u32  height = lily_config_get_i32("Display", "Height", 600);
    u8   fps    = lily_config_get_i32("Display", "FPS", 60);
    bool vsync  = lily_config_get_bool("Display", "VSYNC", true);

    InitAudioDevice();
    InitWindow(width, height, title);
    SetTargetFPS(fps);

    if (vsync) {
        SetWindowState(FLAG_VSYNC_HINT);
    }

    lily_assets_load();

    scene_manager_init();
    scene_manager_change(params.start);

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

    lily_assets_unload();

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
