#define STB_IMAGE_IMPLEMENTATION

#include <GL/glut.h>
#include "../include/variables.h"
#include "../include/vec3f.h"
#include "../include/renderer.h"
#include "../include/terrain.h"
#include "../include/imageloader.h"
#include "../include/helper_functions.h"
#include "../include/buildings.h"

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
	glNormal3f(FSCALE * (X_OFF +  normal[0]), FSCALE * (Y_OFF +  normal[1]), FSCALE * (Z_OFF +  normal[2]));
	// cout<<x<<" "<<z<<endl;
	glTexCoord2f((float)(x)/1200,(float)(z)/1200);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->get_height(x, z)), FSCALE * (Z_OFF +  z));

	normal = _terrain->get_normal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	glTexCoord2f((float)(x)/1200,(float)(z+1)/1200);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->get_height(x, z + 1)), FSCALE * (Z_OFF +  (z + 1)));
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

Vec3f ver[8] = 
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

void quad(int a,int b,int c,int d, GLuint building_texture, Vec3f offset,vector<Vec3f> vertices)
{
	//  125 is the global offset
	Vec3f goff = Vec3f(X_OFF,Y_OFF - 125,Z_OFF);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, building_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(((vertices[a] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(((vertices[b] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(((vertices[c] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(((vertices[d] + offset + goff) * FSCALE).to_float());

    glEnd();
}

void render_building(GLuint building_texture, Vec3f offset, vector<Vec3f> vertices) {
	// the coordinates ordering must be clockwise.
    quad(2,7,4,3,building_texture,offset,vertices); //top
    quad(1,6,5,0,building_texture,offset,vertices); //bottom
    quad(4,7,6,5,building_texture,offset,vertices); //front
    quad(0,1,2,3,building_texture,offset,vertices); //back
    quad(3,4,5,0,building_texture,offset,vertices); //left
    quad(7,2,1,6,building_texture,offset,vertices); //right
}

void render_all_buildings() {
	render_building(build1_texture,Vec3f(0,0,0), buliding_struct_1);
	render_building(build1_texture,Vec3f(100,0,0), buliding_struct_2);
	render_building(build1_texture,Vec3f(0,0,100), buliding_struct_3);
	render_building(build1_texture,Vec3f(0,0,250), buliding_struct_4);
	render_building(build1_texture,Vec3f(250,0,0), buliding_struct_5);
	render_building(build1_texture,Vec3f(400,0,0), buliding_struct_6);
	render_building(build1_texture,Vec3f(0,0,400), buliding_struct_7);
	render_building(build1_texture,Vec3f(400,0,400), buliding_struct_8);
	render_building(build1_texture,Vec3f(250,0,250), buliding_struct_9);
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

	render_all_buildings();
	
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

	image = loadBMP("./resources/build1.bmp");
	build1_texture = loadTexture(image);
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
