project('lily', 'c')

raylib = subproject('raylib', default_options: ['default_library=static'])
raylib_dep = raylib.get_variable('raylib_dep')
raylib_inc = raylib.get_variable('raylib_inc')

miniz = subproject('miniz', default_options: ['default_library=static'])
miniz_dep = miniz.get_variable('miniz_dep')

inih = subproject('inih', default_options: ['default_library=static'])
inih_dep = inih.get_variable('inih_dep')
inih_inc = inih.get_variable('inc_inih')

lily_inc = include_directories('./include')
rstb_inc = include_directories('./external/rstb')

os = host_machine.system()
os_is_emscripten = (os == 'emscripten')
os_is_windows = (os == 'windows')
os_is_linux = (os == 'linux')

bash = find_program('bash')
name = meson.project_name()
root = meson.current_source_dir()
build = meson.current_build_dir()
resource_src = root / 'resources'
asset_src = resource_src / 'assets'
pkg_script = root / 'scripts' / 'package_asset.sh'
dist_path = root / 'dist'
resources_files = [
  'resources/lily.ini',
]
if os_is_emscripten
  resources_files = []
  resources_files += 'index.html'
  meson.add_install_script(
    'sh',
    '-c', 'cp '
    + (root / 'index.html')
    + ' '
    + dist_path
    + ' && '
    + 'cp '
    + (build / 'src' / 'game' / name)
    + '.data'
    + ' '
    + dist_path,
  )
else
  custom_target(
    'package_assets',
    output: 'data.zip',
    command: [
      bash,
      pkg_script,
      asset_src,
      '@OUTPUT@',
    ],
    build_by_default: true,
    install: true,
    install_dir: dist_path,
  )
endif
install_data(resources_files, install_dir: dist_path)

subdir('src')
