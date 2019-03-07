#include "terrain.h"
#include "vec3f.h"
#include "imageloader.h"

#include<bits/stdc++.h>

using namespace std;

Terrain::Terrain(const char* filename, float height) {
    
}

Terrain* Terrain::load_image(const char* filename, float height) {
    Image* image = loadBMP(filename);
	Terrain* t = this;
	for(int y = 0; y < image->height; y++) {
		for(int x = 0; x < image->width; x++) {
			unsigned char color =
				(unsigned char)image->pixels[3 * (y * image->width + x)];
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
		}
	}
	
	delete image;
	t->computeNormals();
	return t;
}