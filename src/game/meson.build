game_src = files('main.c')

game_inc = include_directories('.')

c_args = []
exe_deps = [lily_dep]
link_args = []
if os_is_emscripten
  c_args += '-O2'
  c_args += '-DPLATFORM_WEB'
  link_args += '--preload-file'
  link_args += resource_src / 'data.zip' + '@data.zip'
  link_args += '--preload-file'
  link_args += resource_src / 'lily.ini' + '@lily.ini'
  link_args += '--exclude-file'
  link_args += asset_src
  exe_deps += zip_copy_dep
endif
link_args += '-lm'

executable(
  name,
  game_src,
  dependencies: exe_deps,
  include_directories: [game_inc, rstb_inc, lily_inc],
  link_args: link_args,
  c_args: c_args,
  install: true,
  install_dir: dist_path,
)
