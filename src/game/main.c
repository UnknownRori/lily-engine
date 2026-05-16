#include "lily/2d/rendering.h"
#include "lily/anim/easing.h"
#include "lily/anim/tween.h"
#include "lily/anim/tween_def.h"
#include "lily/engine.h"
#include "lily/math.h"
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

    render2d_pipeline_t* p;
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
    demo->p = render2d_pipeline_init(
        .reserve = 128,
    );
    return demo;
}

static void  Update(f32 dt, void* data)
{
    Demo* demo = data;
    if ((demo->x) < 0 || demo->x > (SCR_W - demo->radius)) {
        demo->xv *= -1.;
    }

    if ((demo->y) < 0 || demo->y > (SCR_H - demo->radius)) {
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
    ClearBackground((Color) {.r = 69, .g = 69, .b = 69, .a = 255});
    render2d_push_rect(
        demo->p, 69, 
        .tint = demo->c,
        .size = VEC2(demo->radius, demo->radius),
        .pos  = VEC2(demo->x, demo->y)
    );
    render2d_pipeline_flush(demo->p);
}

static void  Unload(void* data)
{
    RORI_FREE(data);
}

int main()
{
    lily_engine_init(
        .width  = SCR_W,
        .height = SCR_H,
        .fps    = 60,
        .start  = { .init = Init, .render = Render, .update = Update, .unload = Unload },
        .read_engine_ini = true,
    );

    lily_engine_run();
}
