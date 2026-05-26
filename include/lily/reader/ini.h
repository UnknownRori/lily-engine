////////////////////////////////////////////////////
///
/// File: reader/ini.h
/// Desc:
///     This file contains helper function for handling reading a .ini file
///     currently it allocate everything on stack
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "../types.h"

typedef struct lily_ini_t lily_ini_t;

lily_ini_t*         lily_ini_parse      (const char* buffer, bool* status);
void                lily_ini_free       (lily_ini_t*);
bool                lily_ini_get_bool   (lily_ini_t*, const char* section, const char* key, bool fallback);
i32                 lily_ini_get_i32    (lily_ini_t*, const char* section, const char* key, i32 fallback);
f32                 lily_ini_get_f32    (lily_ini_t*, const char* section, const char* key, f32 fallback);
const char*         lily_ini_get_cstr   (lily_ini_t*, const char* section, const char* key, const char* fallback);
