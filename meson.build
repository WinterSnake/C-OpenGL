# -Project
project('opengl', 'c', version: '1.0.0', default_options: {'warning_level': '2'})

# -Compiler
cc = meson.get_compiler('c')

# -Dependencies
depgl = dependency('opengl')
depglfw = dependency('glfw3')
depmath = cc.find_library('m', required: true)

# -Output
executable('opengl', sources: ['./src/main.c', './src/glad.c', './src/color.c', './src/shader.c'], include_directories: './include', dependencies: [depgl, depglfw, depmath])
