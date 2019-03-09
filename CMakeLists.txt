cmake_minimum_required( VERSION 3.0 )

project( 3d_map_simulator )

# Define
set(CMAKE_CXX_STANDARD 14)
set(SRC_FILES ./src/imageloader.cpp ./src/renderer.cpp ./src/terrain.cpp ./src/vec3f.cpp ./src/main.cpp)
set(CMAKE_CXX_FLAGS "-std=c++14 -lglut -lGLU -lGL")

# flags
add_definitions(${CMAKE_CXX_FLAGS})

# include files
include_directories(./include)


# target
add_executable( 3d_map_simulator  ${SRC_FILES} )