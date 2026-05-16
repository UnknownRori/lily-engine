#include "lily/timer.h"
#include "lily/assert.h"

void timer_init         (lily_timer_t* t, f32 lifetime, bool repeating)
{
    RORI_ASSERT(t != NULL && "Timer must not null");
    t->m_lifetime  = lifetime;
    t->m_remaining = lifetime;
    t->m_completed = false;
    t->m_repeating = repeating;
    t->m_paused    = false;
    t->m_previously_completed = false;
}

void timer_reset        (lily_timer_t* t)
{
    RORI_ASSERT(t != NULL && "Timer must not null");
    timer_init(t, t->m_lifetime, t->m_repeating);
}

void timer_update       (lily_timer_t* t, f32 dt)
{
    RORI_ASSERT(t != NULL && "Timer must not null");

    if (t->m_paused) return;
    t->m_previously_completed = t->m_completed;
    if (t->m_completed && t->m_repeating) timer_reset(t);
    if (!t->m_repeating) t->m_completed = false;
    t->m_remaining -= dt;
    if (t->m_remaining <= 0.0) t->m_completed = true;
}

bool timer_is_completed (const lily_timer_t* t)
{
    RORI_ASSERT(t != NULL && "Timer must not null");
    return t->m_completed;
}

bool timer_is_done      (const lily_timer_t* t)
{
    RORI_ASSERT(t != NULL && "Timer must not null");
    return !(t->m_lifetime > 0.);
}

f32  timer_progress     (const lily_timer_t* t)
{
    RORI_ASSERT(t != NULL && "Timer must not null");
    return t->m_remaining / t->m_lifetime;
}
