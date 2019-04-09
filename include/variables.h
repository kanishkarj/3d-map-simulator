#ifndef VARIABLES_H
#define VARIABLES_H

// Model Variables
float FSCALE = 100.0f; 
const int X_OFF = 0; 
const int Y_OFF = 0; 
const int Z_OFF = 0;

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
float zNear=0.1;
float zFar=20;

// Object Variables
GLuint ground_texture, 
build1_texture, build2_texture, build3_texture, build4_texture, 
build5_texture, build6_texture, build_top, 
sky_afternoon1, sky_afternoon2, sky_afternoon3, sky_afternoon4,
sky_morning1, sky_morning2, sky_morning3, sky_morning4,
sky_evening1, sky_evening2, sky_evening3, sky_evening4, 
sky_night1, sky_night2, sky_night3, sky_night4; 

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