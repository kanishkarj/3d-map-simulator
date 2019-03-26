#include <GL/glut.h>
#include "../include/renderer.h"
#include "../include/terrain.h"

float _anglex = 0.0f;
float _angley = 0.0f;
float _anglez = 0.0f;

float FSCALE = 1.0f; 
int X_OFF = 0; 
int Y_OFF = 0; 
int Z_OFF = 0;

extern Terrain* _terrain;

void update(int value){
    //  _anglex += 1.0f;
	 if (_anglex > 360) {
	 	_anglex -= 360;
	 }
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void specialKeys( unsigned char key, int x, int y ) 
{
	switch(key) {
        
		// Coordinate Translations positive
		case 'i' : {
			X_OFF += 25;
            break;
        };
		case 'j' : {
			Y_OFF += 25;
            break;
        };
		case 'k' : {
			Z_OFF += 25;
            break;
        };

		// Coordinate Translations negative
		case 'I' : {
			X_OFF -= 25;
            break;
        };
		case 'J' : {
			Y_OFF -= 25;
            break;
        };
		case 'K' : {
			Z_OFF -= 25;
            break;
        };


		// Scale/Zoom in and out
        case 's' : {
			FSCALE += 0.02f;
            break;
        };
        case 'S' : {
			FSCALE -= 0.02f;
            break;
        };

		// miscellaneous commands
        case 'r' : {
			FSCALE = 0.0f;
			X_OFF = 0;
			Y_OFF = 0;
			Z_OFF = 0;
            break;
        };

		// Rotation commands
		case 'x' : {
			_anglex += 1.0f;
			break;
		}
		case 'X' : {
	    	_anglex -= 1.0f;
			break;
		}
		case 'y' : {
			_angley += 1.0f;
			break;
		}
		case 'Y' : {
	    	_angley -= 1.0f;
			break;
		}
		case 'z' : {
			_anglez += 1.0f;
			break;
		}
		case 'Z' : {
	    	_anglez -= 1.0f;
			break;
		}
	}
}

void render_points(Vec3f normal,int x,int z) {
	glNormal3f(X_OFF + FSCALE * normal[0], Y_OFF + FSCALE * normal[1], Z_OFF + FSCALE * normal[2]);
			
	glVertex3f(X_OFF + FSCALE * x, Y_OFF + FSCALE * _terrain->get_height(x, z), Z_OFF + FSCALE * z);
	normal = _terrain->get_normal(x, z + 1);

	glNormal3f(X_OFF + FSCALE * normal[0], Y_OFF + FSCALE * normal[1], Z_OFF + FSCALE * normal[2]);
	glVertex3f(X_OFF + FSCALE * x, Y_OFF + FSCALE * _terrain->get_height(x, z + 1), Z_OFF + FSCALE * (z + 1));
}

void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	
	glRotatef(-_anglex, 1.0f, 0.0f, 0.0f);
	glRotatef(-_angley, 0.0f, 1.0f, 0.0f);
	glRotatef(-_anglez, 0.0f, 0.0f, 1.0f);
	
	// GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	// GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	// GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	// glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	float scale = 5.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float)(_terrain->width() - 1) / 2,
				 0.0f,
				 -(float)(_terrain->length() - 1) / 2);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int z = 0; z < _terrain->length() - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < _terrain->width(); x++) {
			Vec3f normal = _terrain->get_normal(x, z);
			render_points(normal,x,z);
		}
		glEnd();
	}
	
	glutSwapBuffers();
}

void handleResize(int w, int h){
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void initRendering(){
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void handleKeypress(unsigned char key, int x, int y){
    switch (key) {
		case 27:
			cleanup();
			exit(0);
	}
}

void cleanup() {

}
