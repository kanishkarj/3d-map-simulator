cmake_minimum_required( VERSION 3.0 )

project( 3d_map_simulator )

# Define
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lglut -lGLU -lGL")

# flags
add_definitions(${OPENGL_FLAGS})

# include files
include_directories( ./include )

# target
add_executable( 3d_map_simulator ./src/imageloader.cpp ./src/renderer.cpp ./src/terrain.cpp ./src/vec3f.cpp ./src/main.cpp  )