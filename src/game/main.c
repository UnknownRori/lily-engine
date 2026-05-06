/*#include "lily/engine.h"*/
/*int main()*/
/*{*/
/*    lily_engine_init(*/
/*        .width  = 800,*/
/*        .height = 600,*/
/*        .fps    = 60,*/
/*    );*/
/**/
/*    lily_engine_run();*/
/*}*/

#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static void UpdateGame()
{
    //
}


int main()
{
    InitWindow(800, 600, "a");
    SetTargetFPS(60);
    InitAudioDevice();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateGame, 0, 1);
#else
    while (!WindowShouldClose()) {
        UpdateGame();
    }
#endif


    return 0;
}
