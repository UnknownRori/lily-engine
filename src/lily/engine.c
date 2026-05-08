#include <raylib.h>
#include "lily/engine.h"
#include "lily/types.h"

#include "./scene_manager.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static bool lily_should_exit();
static void lily_update();

rori_status_t lily_engine_init_impl(lily_engine_param params)
{
    if (params.title == NULL) {
        params.title = "Lily";
    }

    InitAudioDevice();
    InitWindow(params.width, params.height, params.title);
    SetTargetFPS(params.fps);

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
