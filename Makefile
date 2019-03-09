build/simulator :
	g++ src/terrain.cpp src/vec3f.cpp src/imageloader.cpp src/renderer.cpp src/main.cpp  -lglut -lGLU -lGL -o build/simulator

run : build/simulator 
	./build/simulator