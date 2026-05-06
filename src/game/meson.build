game_src = files('main.c')

game_inc = include_directories('.')

executable(
  meson.project_name(),
  game_src,
  dependencies: [lily_dep],
  link_with: [lily_lib],
  include_directories: [game_inc, lily_inc],
)
