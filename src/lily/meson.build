lily_priv_inc = include_directories('.')
lily_src = files(
  '2d/rendering.c',
  'anim/easing.c',
  'anim/tween.c',
  'anim/tween_def.c',
  'ini/engine_config.c',
  'reader/ini.c',
  'assets.c',
  'engine.c',
  'scene_manager.c',
  'timer.c',
  'zip.c',
)

c_args = []
lily_dep_list = [raylib_dep, inih_dep, miniz_dep]
lily_inc_list = [lily_inc, rstb_inc, lily_priv_inc, miniz_inc]
if os_is_emscripten or os_is_linux
  c_args += '-O2'
  lily_lib = static_library(
    'lily',
    lily_src,
    c_args: c_args,
    dependencies: lily_dep_list,
    include_directories: lily_inc_list,
  )
else
  lily_lib = library(
    'lily',
    lily_src,
    dependencies: lily_dep_list,
    include_directories: lily_inc_list,
    install: true,
    install_dir: dist_path,
  )
endif

lily_dep = declare_dependency(
  link_with: [lily_lib],
  include_directories: [lily_inc, rstb_inc, raylib_inc],
)
