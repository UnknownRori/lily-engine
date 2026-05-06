project('lily', 'c')

raylib = subproject('raylib', default_options: ['default_library=static'])
raylib_dep = raylib.get_variable('raylib_dep')
raylib_inc = raylib.get_variable('raylib_inc')

lily_inc = include_directories('./include')

subdir('src')
