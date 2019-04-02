#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

void update(int value);
void drawScene();
void handleResize(int w, int h);
void initRendering();
void keyboard(unsigned char,int,int);
void mouse(int,int);
void cleanup();

#endif