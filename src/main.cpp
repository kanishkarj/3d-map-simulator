#include<bits/stdc++.h>
#include <GL/glut.h>

#include <3d_map_simulator/vec3f.h>
#include <3d_map_simulator/terrain.h>
#include <3d_map_simulator/imageloader.h>
#include <3d_map_simulator/renderer.h>

Terrain* _terrain = new Terrain("../resources/test.bmp", 300);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("3D Map simulator");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}
