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
float limit=89.0*M_PI/180.0f;


void keyboard(unsigned char key,int x,int y){
	switch (key) {
		case 27 :
			cleanup();
			exit(0);
		case ' ':
			mode=!mode;
		case 'w' :
			cam_x += lx * speed ;
			cam_y += ly * speed ;
			cam_z += lz * speed ;
			break;
		case 's' :
			cam_x -= lx * speed ;
			cam_y -= ly * speed ;
			cam_z -= lz * speed ;
			break;
		case 'a' :
			cam_x += cos(pitch) * sin(yaw - M_PI_2) * speed ;
			cam_z += -cos(pitch) * cos(yaw - M_PI_2) * speed ;
			break;
		case 'd' :
			cam_x += cos(pitch) * sin(yaw + M_PI_2) * speed ;
			cam_z += -cos(pitch) * cos(yaw + M_PI_2) * speed ;
			break;
		case 'i' :
			cam_y += speed ;
			break;
		case 'j': 
			cam_y -= speed ;
			break;
		case 'f':
			if(!full_screen){
				glutFullScreen();
				full_screen=1;
			}
			else{
				glutReshapeWindow(400,400);
				full_screen=0;
			}
			break;
	}
	glutPostRedisplay();
}

void mouse(int mx,int my){
	if(mode){
		if(warped){
			warped=false;
			return;
		}
		pitch += (200-my)*rot_speed;
		if(pitch>=limit) pitch=limit;
		else if(pitch<=-limit) pitch= -limit;
		yaw += (mx-200)*rot_speed;
		glutWarpPointer(200,200);
		lx = cos(pitch)*sin(yaw);
		ly = sin(pitch);
		lz = -cos(pitch)*cos(yaw);
		warped=true;
		glutPostRedisplay();
	}
}

void render_points(Vec3f normal,int x,int z) {
	glNormal3f(FSCALE * (X_OFF +  normal[0]), FSCALE * (Y_OFF +  normal[1]), FSCALE * (Z_OFF +  normal[2]));
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
	//  125 is the error offset
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
    quad(2,7,4,3,build_top,offset,vertices); //top
    quad(1,6,5,0,building_texture,offset,vertices); //bottom
    quad(4,7,6,5,building_texture,offset,vertices); //front
    quad(0,1,2,3,building_texture,offset,vertices); //back
    quad(3,4,5,0,building_texture,offset,vertices); //left
    quad(7,2,1,6,building_texture,offset,vertices); //right
}

void render_all_buildings() {

	// build6_texture goes good with sm buildings

	// first row
	render_building(build6_texture,Vec3f(50,0,50), buliding_struct_1_sm);
	render_building(build2_texture,Vec3f(150,0,50), buliding_struct_3_md);
	render_building(build3_texture,Vec3f(270,0,50), buliding_struct_1_md);
	render_building(build5_texture,Vec3f(380,0,50), buliding_struct_2_md);
	render_building(build1_texture,Vec3f(520,0,50), buliding_struct_2_l);
	render_building(build6_texture,Vec3f(650,0,50), buliding_struct_3_sm);
	render_building(build5_texture,Vec3f(775,0,50), buliding_struct_3_md);
	render_building(build6_texture,Vec3f(875,0,50), buliding_struct_1_sm);
	render_building(build4_texture,Vec3f(1020,0,50), buliding_struct_3_l);

	// last row
	render_building(build6_texture,Vec3f(50,0,1020), buliding_struct_3_sm);
	render_building(build2_texture,Vec3f(150,0,1010), buliding_struct_1_md);
	render_building(build3_texture,Vec3f(270,0,1010), buliding_struct_2_md);
	render_building(build5_texture,Vec3f(380,0,1020), buliding_struct_1_md);
	render_building(build1_texture,Vec3f(520,0,1030), buliding_struct_3_l);
	render_building(build6_texture,Vec3f(620,0,1020), buliding_struct_2_sm);
	render_building(build5_texture,Vec3f(775,0,1010), buliding_struct_1_md);
	render_building(build6_texture,Vec3f(875,0,1020), buliding_struct_3_sm);
	render_building(build4_texture,Vec3f(1020,0,1010), buliding_struct_3_l);


}

void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_x,cam_y,cam_z,cam_x+lx,cam_y+ly,cam_z+lz,0.0f,1.0f,0.0f);
	//cout<<cam_x<<' '<<cam_y<<' '<<cam_z<<endl;
	
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	float scale = 5.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float)(_terrain->width() - 1) / 2, 0.0f, -(float)(_terrain->length() - 1) / 2);
	
	render_terrain(ground_texture);
	
	render_all_buildings();
	
	glutSwapBuffers();
}

void handleResize(int w, int h){
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (double)w / (double)h, 0.01, 200.0);
}

void load_image_resources() {

	Image* image = loadBMP("./resources/terrain_texture.bmp");
	ground_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build1.bmp");
	build1_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build2.bmp");
	build2_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build3.bmp");
	build3_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build4.bmp");
	build4_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build5.bmp");
	build5_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build6.bmp");
	build6_texture = loadTexture(image);
	delete image;

	image = loadBMP("./resources/build_top.bmp");
	build_top = loadTexture(image);
	delete image;
}

void initRendering(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	load_image_resources();
}

void cleanup() {

}