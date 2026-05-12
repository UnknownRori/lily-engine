lily_priv_inc = include_directories('.')
lily_src = files(
  'anim/easing.c',
  'anim/tween.c',
  'anim/tween_def.c',
  'ini/engine_config.c',
  'engine.c',
  'scene_manager.c',
  'timer.c',
)

if os_is_emscripten or os_is_linux
  lily_lib = static_library(
    'lily',
    lily_src,
    dependencies: [raylib_dep, inih_dep],
    include_directories: [lily_inc, lily_priv_inc],
  )
else
  lily_lib = library(
    'lily',
    lily_src,
    dependencies: [raylib_dep, inih_dep],
    include_directories: [lily_inc, lily_priv_inc],
    install: true,
    install_dir: dist_path,
  )
endif

lily_dep = declare_dependency(
  link_with: [lily_lib],
  include_directories: [lily_inc, raylib_inc],
)
