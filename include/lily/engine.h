////////////////////////////////////////////////////
///
/// File: engine.h
/// Desc:
///     This engine lifecycles and required to be initialized once
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "./scenes.h"
#include "./types.h"

typedef struct lily_engine lily_engine;
typedef struct lily_engine_param {
    const char* title;
    u32     width;
    u32     height;
    u8      fps;

    scene_t start;
} lily_engine_param;

#define lily_engine_init(...) lily_engine_init_impl((lily_engine_param) {__VA_ARGS__})
rori_status_t   lily_engine_init_impl(lily_engine_param params);
rori_status_t   lily_engine_run();
