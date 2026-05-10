#include "lily/anim/tween.h"
#include "lily/assert.h"
#include "lily/timer.h"

void tween_base_init    (tween_base_t* self, f32 duration)
{
    RORI_ASSERT(self != NULL);
    timer_init(&self->m_timer, duration, false);
}

void tween_base_update  (tween_base_t* self, f32 dt)
{
    RORI_ASSERT(self != NULL);
    timer_update(&self->m_timer, dt);
}
