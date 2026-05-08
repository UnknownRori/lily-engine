#include <raylib.h>
#include <string.h>

#include "lily/types.h"
#include "lily/assert.h"
#include "./scene_manager.h"

static scene_t current;
static void*   usr;

void scene_manager_init()
{
    memset(&current, 0, sizeof(current));
    usr = NULL;
}

void scene_manager_change(scene_t new)
{
    current = new;
    usr = current.init();
}

void scene_manager_transition_to(scene_t new)
{
    RORI_ASSERT(false && "Not Implemented");
}

void scene_manager_update()
{
    if (current.update == NULL) return;
    f32 dt = GetFrameTime();
    current.update(dt, usr);
}

void scene_manager_render()
{
    if (current.update == NULL) return;
    f32 dt = GetFrameTime();
    current.render(dt, usr);
}
