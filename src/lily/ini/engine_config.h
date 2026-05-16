////////////////////////////////////////////////////
///
/// File: ini/engine_config.h
/// Desc:
///     Internal engine config ini reader
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "lily/types.h"

bool engine_ini_parse(
    char**  title,
    u32*    width,
    u32*    height,
    u8*     fps,
    bool*   vsync
);
