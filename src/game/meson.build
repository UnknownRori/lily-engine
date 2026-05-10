game_src = files('main.c')

game_inc = include_directories('.')

c_args = []
link_args = []
if os_is_emscripten
  c_args += '-O2'
  c_args += '-DPLATFORM_WEB'
  link_args += '--preload-file'
  link_args += resource_src
endif
link_args += '-lm'

executable(
  name,
  game_src,
  dependencies: [lily_dep],
  include_directories: [game_inc, lily_inc],
  link_args: link_args,
  c_args: c_args,
  install: true,
  install_dir: dist_path,
  # dependencies: [lily_dep, raylib_dep],
  # link_with: [lily_lib],
  # include_directories: [game_inc, lily_inc],
)
