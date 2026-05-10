////////////////////////////////////////////////////
///
/// File: anim/tween.h
/// Desc:
///     This file contains helper function abour easing function
///
/// Copyright (c) 2026 UnknownRori, unknownrori@proton.me. All right reserved.
///
////////////////////////////////////////////////////

#pragma once

#include "lily/types.h"

f32 ease_linear         (f32 t);

f32 ease_in_quad        (f32 t);
f32 ease_out_quad       (f32 t);
f32 ease_in_out_quad    (f32 t);

f32 ease_in_cubic       (f32 t);
f32 ease_out_cubic      (f32 t);
f32 ease_in_out_cubic   (f32 t);

f32 ease_in_sine        (f32 t);
f32 ease_out_sine       (f32 t);
f32 ease_in_out_sine    (f32 t);

f32 ease_in_expo        (f32 t);
f32 ease_out_expo       (f32 t);
f32 ease_in_out_expo    (f32 t);

f32 ease_out_elastic    (f32 t);

f32 ease_in_bounce      (f32 t);
f32 ease_out_bounce     (f32 t);
