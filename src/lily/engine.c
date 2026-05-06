#include "lily/engine.h"
#include "lily/types.h"
#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static bool lily_should_exit();
static void lily_update();
static void lily_draw();

rori_status_t lily_engine_init_impl(lily_engine_param params)
{
    if (params.title == NULL) {
        params.title = "Lily";
    }

    InitAudioDevice();
    InitWindow(params.width, params.height, params.title);
    SetTargetFPS(params.fps);

    return RORI_SUCCESS;
}

rori_status_t lily_engine_run()
{
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateGame, 0, 1);
#else
    while (!WindowShouldClose()) {
        if (lily_should_exit()) break;
        lily_update();
        lily_draw();
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

}

static void lily_draw()
{
    BeginDrawing(); {
        ClearBackground(BLACK);
    } EndDrawing();
}
