lily_priv_inc = include_directories('.')
lily_src = files(
  'engine.c',
)

lily_lib = static_library(
  'lily',
  lily_src,
  dependencies: [raylib_dep],
  include_directories: [lily_inc, lily_priv_inc],
)

lily_dep = declare_dependency(
  dependencies: [raylib_dep],
  include_directories: [lily_inc],
  include_directories: [raylib_inc],
)
