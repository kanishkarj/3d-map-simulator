#ifndef VARIABLES_H
#define VARIABLES_H

// Model Variables
float FSCALE = 100.0f; 
int X_OFF = 0; 
int Y_OFF = 0; 
int Z_OFF = 0;

// Camera Variables
float speed = 0.010f * FSCALE;
float rot_speed = 0.001f;
float yaw  =  3.141592653;
float pitch = 0.0f;
float lx = 0.0f,lz = 1.0f,ly = 0.0f;
float cam_x = 307.696,cam_y = -30.0,cam_z =  94.0873;
bool mode  = true;
bool warped = false;
bool full_screen = false;
bool controls = true;
float swidth=800;
float sheight=600;
float fov=20.0;
float zNear=0.01;
float zFar=20;

// Object Variables
GLuint ground_texture, 
build1_texture, build2_texture, build3_texture, build4_texture, 
build5_texture, build6_texture, build_top, 
sky_night, sky_afternoon, sky_morning, sky_evening; 

// Time Variables
enum TimeOfDay {
    Morning,
    Afternoon,
    Evening,
    Night
};
TimeOfDay tod = TimeOfDay::Night;
int time_hr = 22;

#endif