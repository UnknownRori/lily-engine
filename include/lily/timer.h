////////////////////////////////////////////////////
///
/// File: timer.h
/// Desc:
///     This file contains Timer object struct helper
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "./types.h"

typedef struct lily_timer_t {
    f32  m_remaining;
    f32  m_lifetime;
    bool m_repeating;
    bool m_paused;
    bool m_completed;
    bool m_previously_completed;
} lily_timer_t;

void timer_init         (lily_timer_t*, f32 lifetime, bool repeating);
void timer_reset        (lily_timer_t*);
void timer_update       (lily_timer_t*, f32 dt);
bool timer_is_completed (const lily_timer_t*);
bool timer_is_done      (const lily_timer_t*);
f32  timer_progress     (const lily_timer_t*);
