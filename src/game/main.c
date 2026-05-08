#include "lily/engine.h"
#include "lily/memory.h"
#include "lily/types.h"
#include <raylib.h>

#define SCR_W  800
#define SCR_H  600
#define SPEED  100
#define RADIUS 50

typedef struct Demo {
    f32 x, y;
    f32 xv, yv;
} Demo;

static void* Init()
{
    Demo* demo = RORI_MALLOC(sizeof(Demo));
    demo->x  = SCR_W / 2.;
    demo->y  = SCR_H / 2.;
    demo->xv = SPEED;
    demo->yv = SPEED;
    return demo;
}

static void  Update(f32 dt, void* data)
{
    Demo* demo = data;
    if (demo->x - RADIUS < 0 || demo->x > SCR_W - RADIUS) {
        demo->xv *= -1.;
    }

    if (demo->y - RADIUS < 0 || demo->y > SCR_H - RADIUS) {
        demo->yv *= -1.;
    }

    demo->x += demo->xv * dt;
    demo->y += demo->yv * dt;
}

static void  Render(f32 dt, void* data)
{
    Demo* demo = data;
    ClearBackground(GRAY);
    DrawCircle(demo->x, demo->y, RADIUS, RED);
}

static void  Unload(void* data)
{
    RORI_FREE(data);
}

int main()
{
    lily_engine_init(
        .width  = 800,
        .height = 600,
        .fps    = 60,
        .start  = { .init = Init, .render = Render, .update = Update, .unload = Unload },
    );

    lily_engine_run();
}
