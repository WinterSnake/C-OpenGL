# -Project
project('opengl', 'c', version: '1.0.0', default_options: {'warning_level': '2'})

# -Dependencies
depgl = dependency('opengl')
depglfw = dependency('glfw3')

# -Output
executable('opengl', sources: ['./src/main.c', './src/glad.c'], include_directories: './include', dependencies: [depgl, depglfw])
