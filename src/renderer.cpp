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

int xg = 180;
int zg = 150;

void lighting() {
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

void update_local_vars() {
	time_hr %= 24;
	if(time_hr > 4 && time_hr <= 11) {
		lighting();
		tod = TimeOfDay::Morning;
	} else if (time_hr > 11 && time_hr <= 17) {
		lighting();
		tod = TimeOfDay::Afternoon;
	} else if (time_hr > 17 && time_hr <= 19) {
		lighting();
		tod = TimeOfDay::Evening;
	} else if (time_hr > 19) {
		tod = TimeOfDay::Night;
	} 
}

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
		case 't':
			time_hr++;
			cout<<time_hr<<endl;
			break;
		case 'T':
			time_hr--;
			cout<<time_hr<<endl;
			break;

		case 'x':
			xg++;
			cout<<xg<<","<<zg<<endl;
			break;
		case 'X':
			xg--;
			cout<<xg<<","<<zg<<endl;
			break;
		case 'z':
			zg++;
			cout<<xg<<","<<zg<<endl;
			break;
		case 'Z':
			zg--;
			cout<<xg<<","<<zg<<endl;
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
	glTexCoord2f((float)(x)/300,(float)(z)/300);
	glVertex3f(FSCALE * (X_OFF +  x), FSCALE * (Y_OFF +  _terrain->get_height(x, z)), FSCALE * (Z_OFF +  z));

	normal = _terrain->get_normal(x, z + 1);
	glNormal3f((X_OFF +  normal[0]), Y_OFF +  normal[1], Z_OFF +  normal[2]);
	glTexCoord2f((float)(x)/300,(float)(z+1)/300);
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

void quad(int a,int b,int c,int d, GLuint building_texture, Vec3f offset,vector<Vec3f> vertices, float scale)
{
	//  125 is the error offset
	Vec3f goff = Vec3f(X_OFF,Y_OFF - 25,Z_OFF);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, building_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

	glTexCoord2f(0.0f, scale);
	glVertex3fv(((vertices[a] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(scale, scale);
    glVertex3fv(((vertices[b] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(scale, 0.0f);
    glVertex3fv(((vertices[c] + offset + goff) * FSCALE).to_float());

	glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(((vertices[d] + offset + goff) * FSCALE).to_float());

    glEnd();
}

void render_building(GLuint building_texture, Vec3f offset, vector<Vec3f> vertices) {
	// the coordinates ordering must be clockwise.
    quad(2,7,4,3,build_top,offset,vertices, 3.0f); //top
    quad(1,6,5,0,building_texture,offset,vertices, 3.0f); //bottom
    quad(4,7,6,5,building_texture,offset,vertices, 3.0f); //front
    quad(0,1,2,3,building_texture,offset,vertices, 3.0f); //back
    quad(3,4,5,0,building_texture,offset,vertices, 3.0f); //left
    quad(7,2,1,6,building_texture,offset,vertices, 3.0f); //right
}

void render_sky_helper(GLuint building_texture, Vec3f offset, vector<Vec3f> vertices, float scale) {
	// the coordinates ordering must be clockwise.
    quad(2,7,4,3,building_texture,offset,vertices, scale); //top
    quad(1,6,5,0,building_texture,offset,vertices, scale); //bottom
    quad(4,7,6,5,building_texture,offset,vertices, scale); //front
    quad(0,1,2,3,building_texture,offset,vertices, scale); //back
    quad(3,4,5,0,building_texture,offset,vertices, scale); //left
    quad(7,2,1,6,building_texture,offset,vertices, scale); //right
}

void render_all_buildings() {

	// build6_texture goes good with sm buildings

	// first row
	render_building(build6_texture,Vec3f(12.5,0,12.5), buliding_struct_1_sm);
	render_building(build2_texture,Vec3f(37.5,0,12.5), buliding_struct_3_md);
	render_building(build3_texture,Vec3f(67.625,0,12.5), buliding_struct_1_md);
	render_building(build5_texture,Vec3f(95,0,12.5), buliding_struct_2_md);
	render_building(build1_texture,Vec3f(130,0,12.5), buliding_struct_2_l);
	render_building(build6_texture,Vec3f(162.5,0,12.5), buliding_struct_3_sm);
	render_building(build5_texture,Vec3f(193.75,0,12.5), buliding_struct_3_md);
	render_building(build6_texture,Vec3f(218.75,0,12.5), buliding_struct_1_sm);
	render_building(build4_texture,Vec3f(255,0,12.5), buliding_struct_3_l);

	// last row
	render_building(build6_texture,Vec3f(12.5,0,255), buliding_struct_3_sm);
	render_building(build2_texture,Vec3f(37.5,0,252.4), buliding_struct_1_md);
	render_building(build3_texture,Vec3f(67.625,0,252.4), buliding_struct_2_md);
	render_building(build5_texture,Vec3f(95,0,255), buliding_struct_1_md);
	render_building(build1_texture,Vec3f(130,0,257.4), buliding_struct_3_l);
	render_building(build6_texture,Vec3f(155,0,255), buliding_struct_2_sm);
	render_building(build5_texture,Vec3f(193.75,0,252.4), buliding_struct_1_md);
	render_building(build6_texture,Vec3f(218.75,0,255), buliding_struct_3_sm);
	render_building(build4_texture,Vec3f(255,0,252.4), buliding_struct_3_l);

	render_building(build6_texture,Vec3f(197,0,124), buliding_struct_4_xsm);
	render_building(build6_texture,Vec3f(74,0,190), buliding_struct_4_xsm);

	render_building(build6_texture,Vec3f(154,0,120), buliding_struct_5_sm);
	render_building(build6_texture,Vec3f(197,0,197), buliding_struct_5_sm);
	render_building(build6_texture,Vec3f(84,0,145), buliding_struct_6_sm);


	render_building(build6_texture,Vec3f(198,0,80), buliding_struct_6_md);
	render_building(build6_texture,Vec3f(198,0,55), buliding_struct_6_sm);

	render_building(build6_texture,Vec3f(82,0,55), buliding_struct_6_xsm);

	render_building(build6_texture,Vec3f(69,0,82), buliding_struct_1_sm);
	render_building(build6_texture,Vec3f(69,0,119), buliding_struct_1_sm);
	render_building(build6_texture,Vec3f(129,0,142), buliding_struct_1_sm);

	render_building(build6_texture,Vec3f(220,0,177), buliding_struct_1_sm);
	render_building(build6_texture,Vec3f(133,0,190), buliding_struct_4_sm);

	render_building(build6_texture,Vec3f(129,0,74), buliding_struct_5_sm);

	render_building(build6_texture,Vec3f(148,0,51), buliding_struct_6_sm);

}

void render_sky() {
	switch (tod) {
		case TimeOfDay::Night : {
			render_sky_helper(sky_night,Vec3f(-100,-100,-100),sky_coord,3.0f);
			break;
		}
		case TimeOfDay::Afternoon : {
			render_sky_helper(sky_afternoon,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
		case TimeOfDay::Morning : {
			render_sky_helper(sky_morning,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
		case TimeOfDay::Evening : {
			render_sky_helper(sky_evening,Vec3f(-100,-100,-100),sky_coord,1.0f);
			break;
		}
	}
}

void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_x,cam_y,cam_z,cam_x+lx,cam_y+ly,cam_z+lz,0.0f,1.0f,0.0f);
	//cout<<cam_x<<' '<<cam_y<<' '<<cam_z<<endl;
	
	float scale = 5.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float)(_terrain->width() - 1) / 2, 0.0f, -(float)(_terrain->length() - 1) / 2);
	
	render_terrain(ground_texture);
	
	render_all_buildings();
	render_sky();

	glutSwapBuffers();

	update_local_vars();
}

void handleResize(int w, int h){
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (double)w / (double)h, 0.01, 20 * FSCALE);
}

void load_image_resources() {

	ground_texture = loadTx("./resources/terrain_texture.bmp");

	build1_texture = loadTx("./resources/buildings/build1.bmp");
	build2_texture = loadTx("./resources/buildings/build2.bmp");
	build3_texture = loadTx("./resources/buildings/build3.bmp");
	build4_texture = loadTx("./resources/buildings/build4.bmp");
	build5_texture = loadTx("./resources/buildings/build5.bmp");
	build6_texture = loadTx("./resources/buildings/build6.bmp");
	build_top = loadTx("./resources/buildings/build_top.bmp");

	sky_night = loadTx("./resources/sky/night.bmp");
	sky_afternoon = loadTx("./resources/sky/afternoon.bmp");
	sky_evening = loadTx("./resources/sky/evening.bmp");
	sky_morning = loadTx("./resources/sky/morning.bmp");
 
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