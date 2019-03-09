#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

void update(int value);
void drawScene();
void handleResize(int w, int h);
void initRendering();
void handleKeypress(unsigned char key, int x, int y);
void cleanup();

#endif