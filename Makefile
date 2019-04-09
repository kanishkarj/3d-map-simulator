
create :
	g++ -O2 src/terrain.cpp src/vec3f.cpp src/imageloader.cpp src/renderer.cpp src/main.cpp  -lglut -lGLU -lGL -o build/simulator

clean :
	rm build/simulator 

run : create 
	./build/simulator
