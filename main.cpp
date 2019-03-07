#include<bits/stdc++.h>
#include <GL/glut.h>

#include "vec3f.h"
#include "terrain.h"
#include "imageloader.h"
#include "renderer.h"

Terrain* _terrain = new Terrain("heightmap.bmp", 20);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("Terrain - videotutorialsrock.com");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}