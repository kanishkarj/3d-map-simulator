#define STB_IMAGE_IMPLEMENTATION

#include <GL/glut.h>
#include "../include/variables.h"
#include "../include/vec3f.h"
#include "../include/renderer.h"
#include "../include/terrain.h"
#include "../include/imageloader.h"
#include "../include/helper_functions.h"

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
	// cout<<x<<" "<<z<<endl;
	glTexCoord2f((float)(x)/1200,(float)(z)/1200);
	glVertex3f(X_OFF + FSCALE * x, Y_OFF + FSCALE * _terrain->get_height(x, z), Z_OFF + FSCALE * z);

	normal = _terrain->get_normal(x, z + 1);
	glNormal3f(X_OFF + FSCALE * normal[0], Y_OFF + FSCALE * normal[1], Z_OFF + FSCALE * normal[2]);
	glTexCoord2f((float)(x)/1200,(float)(z+1)/1200);
	glVertex3f(X_OFF + FSCALE * x, Y_OFF + FSCALE * _terrain->get_height(x, z + 1), Z_OFF + FSCALE * (z + 1));
}

void render_terrain(GLuint ground_texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground_texture);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int z = 0; z < _terrain->length() - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < _terrain->width(); x++) {
			Vec3f normal = _terrain->get_normal(x, z);
			render_points(normal,x,z);
		}
		glEnd();
	}
}

float ver[8][3] = 
{
    {-100.0,-100.0,100.0},
    {-100.0,100.0,100.0},
    {100.0,100.0,100.0},
    {100.0,-100.0,100.0},
    {-100.0,-100.0,-100.0},
    {-100.0,100.0,-100.0},
    {100.0,100.0,-100.0},
    {100.0,-100.0,-100.0},
};

void quad(int a,int b,int c,int d)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glColor3f(0.5f, 0.6f, 0.4f);
    glBegin(GL_QUADS);

    glVertex3fv(ver[a]);
    glVertex3fv(ver[b]);
    glVertex3fv(ver[c]);
    glVertex3fv(ver[d]);

    glEnd();
}

void render_building() {
    quad(0,3,2,1);
    quad(2,3,7,6);
    quad(0,4,7,3);
    quad(1,2,6,5);
    quad(4,5,6,7);
    quad(0,1,5,4);
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
	
	render_terrain(ground_texture);
	render_building();
	

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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("./resources/terrain_texture.bmp");
	ground_texture = loadTexture(image);
	delete image;

	Image* image = loadBMP("./resources/build1.bmp");
	ground_texture = loadTexture(image);
	delete image;
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
