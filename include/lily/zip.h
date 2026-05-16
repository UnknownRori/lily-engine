////////////////////////////////////////////////////
///
/// File: zip.h
/// Desc:
///     This file contains helper function for loading a zip file and fetching data from it
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////


#pragma once

#include <raylib.h>
#include "lily/types.h"

rori_status_t   lily_load_zip(const char*);
void            lily_unload_zip();

u8*             lily_load_zip_file(const char* file, usize* out_size);
char*           lily_load_zip_text(const char* file);
Image           lily_load_zip_image(const char*);
Texture2D       lily_load_zip_texture2d(const char*);
Font            lily_load_zip_font(const char*, u8 font_size);
Wave            lily_load_zip_wave(const char*);
Sound           lily_load_zip_sound(const char*);
Music           lily_load_zip_music(const char*);
