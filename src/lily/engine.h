////////////////////////////////////////////////////
///
/// File: engine.h
/// Desc:
///     Internal engine declaration
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "lily/types.h"
#include "lily/scenes.h"

typedef struct lily_engine {
    u32     width;
    u32     height;
    u8      fps;
    scene_t start;
} lily_engine;
