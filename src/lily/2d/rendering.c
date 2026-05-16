#include <raylib.h>
#include <rstb_da.h>

#include "lily/2d/rendering.h"
#include "lily/math.h"
#include "lily/assert.h"
#include "lily/memory.h"
#include "lily/types.h"

typedef struct render2d_pipeline_t {
    u32 count;
    u32 capacity;
    render2d_cmd_t* items;

    Shader*          shader;
    RenderTexture2D* target;
} render2d_pipeline_t;

static int sort_z_level(const void* a, const void* b)
{
    const render2d_cmd_t* ra = a;
    const render2d_cmd_t* rb = b;

    if (ra->z < rb->z) return -1;
    if (ra->z > rb->z) return  1;
    return 0;
}

render2d_pipeline_t* render2d_pipeline_init_impl(render2d_pipeline_args args)
{
    if (args.reserve <= 0) {
        args.reserve = 128;
    }

    render2d_pipeline_t* pipeline = RORI_CALLOC(1, sizeof(render2d_pipeline_t));
    rstb_da_reserve(pipeline, args.reserve);
    pipeline->target = args.target;
    pipeline->shader = args.shader;
    return pipeline;
}

void render2d_pipeline_free(render2d_pipeline_t* p)
{
    rstb_da_free(p);
    RORI_FREE(p);
}

void render2d_pipeline_flush(render2d_pipeline_t* p)
{
    RORI_ASSERT(p != NULL);
    qsort(p->items, p->count, sizeof(*p->items), sort_z_level);
    if (p->target) {
        BeginTextureMode(*p->target);
    }
    rstb_da_foreach(render2d_cmd_t, cmd, p) {
        switch(cmd->type) {
            case DRAW2D_RECT: {
                render2d_rect_t* t = &cmd->rect;
                DrawRectangleRec(RECT_V2(t->pos, t->size), t->tint);
            } break;
            case DRAW2D_TEXT: {
                render2d_text_t* t = &cmd->text;
                Font font = GetFontDefault();
                if (t->font != NULL) {
                    font = *t->font;
                }
                DrawTextPro(
                    font, 
                    t->text, 
                    t->pos, 
                    VEC2_ZERO, 
                    t->rot, 
                    t->size, 
                    t->spacing, 
                    t->tint
                );
            } break;
            case DRAW2D_TEXTURE: {
                render2d_texture_t* t = &cmd->texture;
                Rectangle src = t->src;
                if (src.width == 0 || src.height == 0) {
                    src.width  = t->texture.width;
                    src.height = t->texture.height;
                }
                DrawTexturePro(
                    t->texture, 
                    src, 
                    t->dst, 
                    t->origin, 
                    t->rot, 
                    t->tint
                );
            } break;
            case __RENDER2D_CMD_MAX:
                RORI_ASSERT(false && "__RENDER2D_CMD_MAX");
                break;
        }
    }
    rstb_da_reset(p);
    if (p->target) {
        BeginTextureMode(*p->target);
    }
}

#define REGISTER_CMD_PUSH_IMPL(NAME, CMD_TYPE, TYPE, VAR) \
    void render2d_push_##NAME##_impl(render2d_pipeline_t* p, u16 z, TYPE t)             \
    {                                                                                   \
        render2d_cmd_t cmd = (render2d_cmd_t) {                                         \
            .type = CMD_TYPE,                                                           \
            .z    = z,                                                                  \
            .VAR  = t,                                                                  \
        };                                                                              \
                                                                                        \
        rstb_da_append(p, cmd);                                                         \
    }

REGISTER_CMD_PUSH_IMPL(text     , DRAW2D_TEXT   , render2d_text_t   , text);
REGISTER_CMD_PUSH_IMPL(rect     , DRAW2D_RECT   , render2d_rect_t   , rect);
REGISTER_CMD_PUSH_IMPL(texture  , DRAW2D_TEXTURE, render2d_texture_t, texture);
