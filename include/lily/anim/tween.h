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

typedef struct tween_base_t {
    timer_t m_timer;
} tween_base_t;

void tween_base_init    (tween_base_t*, f32 duration);
void tween_base_update  (tween_base_t*, f32 dt);

#define TWEEN(TYPE) tween_##TYPE##_t
#define DEFINE_TWEEN(TYPE)                                  \
    typedef struct {                                        \
        tween_base_t base;                                  \
        TYPE    m_from, m_to, m_value;                      \
    } TWEEN(TYPE);                                          \
    void tween_##TYPE##_init(TWEEN(TYPE)*, f32 duration);   \
    void tween_##TYPE##_update(TWEEN(TYPE)*, f32 dt);

