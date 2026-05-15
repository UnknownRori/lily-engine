////////////////////////////////////////////////////
///
/// File: tween.h
/// Desc:
///     This file contains Generic Tween object
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include <raylib.h>
#include "lily/types.h"
#include "lily/timer.h"

typedef f32(*ease_fn)(f32);
typedef struct tween_base_t {
    lily_timer_t m_timer;
    ease_fn easing;
} tween_base_t;

void tween_base_init    (tween_base_t*, f32 duration, ease_fn fn);
void tween_base_update  (tween_base_t*, f32 dt);

#define TWEEN(TYPE) tween_##TYPE##_t
#define TWEEN_INIT(TYPE, ...) tween_##TYPE##_init(__VA_ARGS__)
#define TWEEN_EVALUATE(TYPE, ...) tween_##TYPE##_evaluate(__VA_ARGS__)
#define DEFINE_TWEEN(TYPE)                                                              \
    typedef struct {                                                                    \
        tween_base_t base;                                                              \
    } TWEEN(TYPE);                                                                      \
    void tween_##TYPE##_init(TWEEN(TYPE)*, f32 duration, ease_fn fn);                   \
    TYPE tween_##TYPE##_evaluate(TWEEN(TYPE)*, f32 dt, TYPE start, TYPE end);

#define DEFINE_TWEEN_IMPL_INIT(TYPE)                                        \
    void tween_##TYPE##_init(TWEEN(TYPE) *s, f32 duration, ease_fn fn)      \
    {                                                                       \
        RORI_ASSERT(s != NULL);                                             \
        tween_base_init(&s->base, duration, fn);                            \
    }
#define DEFINE_TWEEN_IMPL_EVALUATE(TYPE, LERP_FN)                               \
    TYPE tween_##TYPE##_evaluate(TWEEN(TYPE)*s, f32 dt, TYPE start, TYPE end)   \
    {                                                                           \
        RORI_ASSERT(s != NULL);                                                 \
        tween_base_update(&s->base, dt);                                        \
        f32 t     = timer_progress(&s->base.m_timer);                           \
        f32 eased = s->base.easing(t);                                          \
        return LERP_FN(start, end, eased);                                      \
    }
