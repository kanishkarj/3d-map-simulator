#ifndef VARIABLES_H
#define VARIABLES_H


// Camera Variables
float speed=0.05f;
float rot_speed=0.001f;
float yaw=0.0f;
float pitch=0.0f;
float lx=0.0f,lz=-1.0f,ly=0.0f;
float cam_x=-0.5f,cam_z=0.0f,cam_y=-0.2f;
bool mode =false;
bool warped=false;

float FSCALE = 1.0f; 
int X_OFF = 0; 
int Y_OFF = 0; 
int Z_OFF = 0;

GLuint ground_texture, build1_texture, build2_texture, build3_texture, build4_texture, build5_texture, build6_texture, build_top; 

#endif