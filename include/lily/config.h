////////////////////////////////////////////////////
///
/// File: config.h
/// Desc:
///     This file contain engine configuration loaded at initialization
///     the configuration is from `lily.ini`
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "lily/types.h"

bool        lily_config_get_bool    (const char* section, const char* key, bool fallback);
i32         lily_config_get_i32     (const char* section, const char* key, i32 fallback);
f32         lily_config_get_f32     (const char* section, const char* key, f32 fallback);
const char* lily_config_get_cstr    (const char* section, const char* key, const char* fallback);
