#include "lily/anim/tween_def.h"
#include "lily/anim/tween.h"
#include "lily/assert.h"
#include "lily/timer.h"
#include "raylib.h"

#include <raymath.h>

DEFINE_TWEEN_IMPL_INIT(f32);
DEFINE_TWEEN_IMPL_INIT(Vector2);
DEFINE_TWEEN_IMPL_INIT(Color);

DEFINE_TWEEN_IMPL_EVALUATE(f32, Lerp);
DEFINE_TWEEN_IMPL_EVALUATE(Vector2, Vector2Lerp);
DEFINE_TWEEN_IMPL_EVALUATE(Color, ColorLerp);

