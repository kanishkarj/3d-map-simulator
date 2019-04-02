#ifndef VARIABLES_H
#define VARIABLES_H


// Camera Variables
float speed=0.5f;
float rot_speed=0.001f;
float yaw = 3.141592653;
float pitch=0.0f;
float lx=0.0f,lz=1.0f,ly=0.0f;
float cam_x=18.2913,cam_y=-4.48757,cam_z= -1.70081;
bool mode =false;
bool warped=false;
bool full_screen=false;

float FSCALE = 10.0f; 
int X_OFF = 0; 
int Y_OFF = 0; 
int Z_OFF = 0;

GLuint ground_texture, build1_texture, build2_texture, build3_texture, build4_texture, build5_texture, build6_texture, build_top; 

#endif