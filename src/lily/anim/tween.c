#include "lily/anim/tween.h"
#include "lily/assert.h"
#include "lily/timer.h"

void tween_base_init    (tween_base_t* self, f32 duration, ease_fn fn)
{
    RORI_ASSERT(self != NULL);
    timer_init(&self->m_timer, duration, false);
    self->easing = fn;
}

void tween_base_update  (tween_base_t* self, f32 dt)
{
    // TODO : Give wrap around logic
    RORI_ASSERT(self != NULL);
    if (timer_is_completed(&self->m_timer)) return;
    timer_update(&self->m_timer, dt);
}
