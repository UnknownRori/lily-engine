project('lily', 'c')

os = host_machine.system()
os_is_emscripten = (os == 'emscripten')
os_is_windows = (os == 'windows')
os_is_linux = (os == 'linux')

dist_path = meson.current_source_dir() + '/dist'

raylib = subproject('raylib', default_options: ['default_library=static'])
raylib_dep = raylib.get_variable('raylib_dep')
raylib_inc = raylib.get_variable('raylib_inc')

lily_inc = include_directories('./include')

bash = find_program('bash')
name = meson.project_name()
root = meson.current_source_dir()
build = meson.current_build_dir()
resource_src = meson.current_source_dir() / 'resources/assets'
asset_src = resource_src / '/assets'
pkg_script = root / 'scripts' / 'package_asset.sh'
resources_files = [
  'resources/lily.ini',
]
if os_is_emscripten
  resources_files = []
  resources_files += 'index.html'
  resources_files += build / 'src/game' / name + '.data'
endif
if not os_is_emscripten
  data_zip = custom_target(
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
