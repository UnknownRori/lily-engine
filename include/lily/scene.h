////////////////////////////////////////////////////
///
/// File: scenes.h
/// Desc:
///     This file contains interface of the scenes
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "./types.h"

typedef void*(*scene_init_f)  ();
typedef void (*scene_update_f)(f32 dt, void* usr_data);
typedef void (*scene_render_f)(f32 dt, void* usr_data);
typedef void (*scene_unload_f)(void*);

typedef struct scene_t {
    scene_init_f   init;
    scene_unload_f unload;
    scene_update_f update;
    scene_render_f render;
} scene_t;

void scene_manager_change(scene_t);
void scene_manager_transition_to(scene_t);

