////////////////////////////////////////////////////
///
/// File: 2d/rendering.h
/// Desc:
///     This file contains 2d rendering pipeline
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include <raylib.h>
#include "lily/types.h"

typedef enum render2d_cmd_type_t {
    DRAW2D_RECT,
    DRAW2D_TEXT,
    DRAW2D_TEXTURE,
    __RENDER2D_CMD_MAX,
} render2d_cmd_type_t;

typedef struct render2d_rect_t {
    Vector2 pos;
    Vector2 size;
    Color   tint;
} render2d_rect_t;

typedef struct render2d_texture_t {
    Texture2D   texture;
    Rectangle   src, dst;
    Vector2     origin;
    f32         rot;
    Color       tint;
} render2d_texture_t;

typedef struct render2d_text_t {
    char*       text;
    Font*       font;
    Vector2     pos;
    f32         size;
    f32         spacing;
    f32         rot;
    Color       tint;
} render2d_text_t;

typedef struct render2d_cmd_t {
    render2d_cmd_type_t type;
    u16 z;
    union {
        render2d_rect_t     rect;
        render2d_text_t     text;
        render2d_texture_t  texture;
    };
} render2d_cmd_t;

typedef struct render2d_pipeline_t render2d_pipeline_t;
typedef struct render2d_pipeline_args {
    u32              reserve;
    Shader*          shader; // NULL for no shader usage
    RenderTexture2D* target; // NULL target global
} render2d_pipeline_args;

#define render2d_pipeline_init(...) \
    render2d_pipeline_init_impl((render2d_pipeline_args) {__VA_ARGS__})
render2d_pipeline_t* render2d_pipeline_init_impl(render2d_pipeline_args);
void render2d_pipeline_flush(render2d_pipeline_t*);
void render2d_pipeline_free(render2d_pipeline_t*);

#define render2d_push_rect(P, Z, ...) \
    render2d_push_rect_impl(P, Z, (render2d_rect_t) {__VA_ARGS__})
void render2d_push_rect_impl(render2d_pipeline_t*, u16, render2d_rect_t);

#define render2d_push_text(P, Z, ...) \
    render2d_push_text_impl(P, Z, (render2d_text_t) {__VA_ARGS__})
void render2d_push_text_impl(render2d_pipeline_t*, u16, render2d_text_t);

#define render2d_push_texture(P, Z, ...) \
    render2d_push_texture_impl(P, Z, (render2d_texture_t) {__VA_ARGS__})
void render2d_push_texture_impl(render2d_pipeline_t*, u16, render2d_texture_t);
