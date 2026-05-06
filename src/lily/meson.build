lily_priv_inc = include_directories('.')
lily_src = files(
  'engine.c',
)

if os_is_emscripten or os_is_linux
  lily_lib = static_library(
    'lily',
    lily_src,
    dependencies: [raylib_dep],
    include_directories: [lily_inc, lily_priv_inc],
  )
else
  lily_lib = library(
    'lily',
    lily_src,
    dependencies: [raylib_dep],
    include_directories: [lily_inc, lily_priv_inc],
    install: true,
    install_dir: dist_path,
  )
endif

lily_dep = declare_dependency(
  link_with: [lily_lib],
  include_directories: [lily_inc, raylib_inc],
)
