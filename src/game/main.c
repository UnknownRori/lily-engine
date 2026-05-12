#include "lily/anim/easing.h"
#include "lily/anim/tween.h"
#include "lily/anim/tween_def.h"
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
    f32 radius;

    Color           c;
    tween_f32_t     bounce;
    tween_Color_t   color;
} Demo;

static void* Init()
{
    Demo* demo = RORI_MALLOC(sizeof(Demo));
    demo->radius = RADIUS;
    demo->x  = SCR_W / 2.;
    demo->y  = SCR_H / 2.;
    demo->xv = SPEED;
    demo->yv = SPEED;
    TWEEN_INIT(f32  , &demo->bounce, 2.0, ease_in_sine);
    TWEEN_INIT(Color, &demo->color , 2.0, ease_in_sine);
    return demo;
}

static void  Update(f32 dt, void* data)
{
    Demo* demo = data;
    if (demo->x - demo->radius < 0 || demo->x > SCR_W - demo->radius) {
        demo->xv *= -1.;
    }

    if (demo->y - demo->radius < 0 || demo->y > SCR_H - demo->radius) {
        demo->yv *= -1.;
    }

    demo->x += demo->xv * dt;
    demo->y += demo->yv * dt;
    demo->radius = TWEEN_EVALUATE(f32, &demo->bounce, dt, 50, 100);
    demo->c      = TWEEN_EVALUATE(Color, &demo->color, dt, RED, GREEN);
}

static void  Render(f32 dt, void* data)
{
    Demo* demo = data;
    ClearBackground(GRAY);
    DrawCircle(demo->x, demo->y, demo->radius, demo->c);
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
        .read_engine_ini = true,
    );

    lily_engine_run();
}
