////////////////////////////////////////////////////
///
/// File: assets.h
/// Desc:
///     This file asset management that uses zip file as packaging mechanism
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include <raylib.h>

Image     lily_get_image(const char* name);
Texture2D lily_get_texture2d(const char* name);
Font      lily_get_font(const char* name);
Sound     lily_get_sound(const char* name);
Music     lily_get_music(const char* name);
