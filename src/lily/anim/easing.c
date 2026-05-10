#include <math.h>
#include <raylib.h>
#include "lily/anim/easing.h"

f32 ease_linear         (f32 t)
{
    return t;
}

f32 ease_in_quad        (f32 t)
{
    return t * t;
}
f32 ease_out_quad       (f32 t)
{
    return t * (2.0f - t);
}
f32 ease_in_out_quad    (f32 t)
{
    return t < 0.5 ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

f32 ease_in_cubic       (f32 t)
{
    return t * t * t;
}
f32 ease_out_cubic      (f32 t)
{
    f32 f = t - 1.0f;
    return f * f * f + 1.0f;
}
f32 ease_in_out_cubic   (f32 t)
{
    return t < 0.5f ? 4.0f * t * t * t : (t - 1.0f) * (2.0f * t - 2.0f) * (2.0f * t - 2.0f) + 1.0f;
}

f32 ease_in_sine        (f32 t)
{
    return 1.0f - cosf(t * PI * 0.5f);
}
f32 ease_out_sine       (f32 t)
{
    return sinf(t * PI * 0.5f);
}
f32 ease_in_out_sine    (f32 t)
{
    return 0.5f * (1.0f - cosf(PI * t));
}

f32 ease_in_expo        (f32 t)
{
    return t == 0.0f ? 0.0f : powf(2.0f, 10.0f * t - 10.0f);
}
f32 ease_out_expo       (f32 t)
{
    return t == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * t);
}
f32 ease_in_out_expo    (f32 t)
{
    if (t == 0.0f) return 0.0f;
    if (t == 1.0f) return 1.0f;
    return t < 0.5f
        ? powf(2.0f,  20.0f * t - 10.0f) * 0.5f
        : (2.0f - powf(2.0f, -20.0f * t + 10.0f)) * 0.5f;
}

f32 ease_out_elastic    (f32 t)
{
    if (t == 0.0f) return 0.0f;
    if (t == 1.0f) return 1.0f;
    return powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * (2.0f * PI) / 3.0f) + 1.0f;
}

f32 ease_out_bounce     (f32 t)
{
    if (t < 1.0f / 2.75f)
    {
        return 7.5625f * t * t;
    }
    else if (t < 2.0f / 2.75f)
    {
        t -= 1.5f / 2.75f;
        return 7.5625f * t * t + 0.75f;
    }
    else if (t < 2.5f / 2.75f)
    {
        t -= 2.25f / 2.75f;
        return 7.5625f * t * t + 0.9375f;
    }
    else
    {
        t -= 2.625f / 2.75f;
        return 7.5625f * t * t + 0.984375f;
    }
}
f32 ease_in_bounce      (f32 t)
{
    return 1.0f - ease_out_bounce(1.0f - t);
}
