#include<bits/stdc++.h>
#include <GL/glut.h>
#include  "../include/vec3f.h"
#include  "../include/terrain.h"
#include  "../include/imageloader.h"
#include  "../include/renderer.h"

Terrain* _terrain = new Terrain("./resources/heightmap.bmp", 300);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("3D Map simulator");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(specialKeys);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}
