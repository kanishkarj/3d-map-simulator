#include "terrain.h"
#include "vec3f.h"
#include "imageloader.h"

#include<bits/stdc++.h>

using namespace std;

Terrain::Terrain(const char* filename, float height) {
	computedNormals = false;
	load_image(filename, height);
	compute_normals();
}

void Terrain::load_image(const char* filename, float height) {
    Image* image = loadBMP(filename);

	this->w =  image->width;
	this->l =  image->height;

	hs = vector<vector<float>>(l, vector<float>(w));
	normals = vector<vector<Vec3f>>(l, vector<Vec3f>(w));
	
	for(int y = 0; y < image->height; y++) {
		for(int x = 0; x < image->width; x++) {
			unsigned char color =
				(unsigned char)image->pixels[3 * (y * image->width + x)];
			float h = height * ((color / 255.0f) - 0.5f);
			this->set_height(x, y, h);
		}
	}
	delete image;
}

Terrain::~Terrain() {
	hs.clear();
	normals.clear();
}

void Terrain::compute_normals() {
	if (computedNormals) {
		return;
	}
	
	//Compute the rough version of the normals
	vector<vector<Vec3f>> normals2 = vector<vector<Vec3f>>(l, vector<Vec3f>(w));
	
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum(0.0f, 0.0f, 0.0f);
			
			Vec3f out;
			if (z > 0) {
				out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
			}
			Vec3f in;
			if (z < l - 1) {
				in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
			}
			Vec3f left;
			if (x > 0) {
				left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
			}
			Vec3f right;
			if (x < w - 1) {
				right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
			}
			
			if (x > 0 && z > 0) {
				sum += out.cross(left).normalize();
			}
			if (x > 0 && z < l - 1) {
				sum += left.cross(in).normalize();
			}
			if (x < w - 1 && z < l - 1) {
				sum += in.cross(right).normalize();
			}
			if (x < w - 1 && z > 0) {
				sum += right.cross(out).normalize();
			}
			
			normals2[z][x] = sum;
		}
	}
	
	//Smooth out the normals
	const float FALLOUT_RATIO = 0.5f;
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum = normals2[z][x];
			
			if (x > 0) {
				sum += normals2[z][x - 1] * FALLOUT_RATIO;
			}
			if (x < w - 1) {
				sum += normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if (z > 0) {
				sum += normals2[z - 1][x] * FALLOUT_RATIO;
			}
			if (z < l - 1) {
				sum += normals2[z + 1][x] * FALLOUT_RATIO;
			}
			
			if (sum.magnitude() == 0) {
				sum = Vec3f(0.0f, 1.0f, 0.0f);
			}
			normals[z][x] = sum;
		}
	}
	
	for(int i = 0; i < l; i++) {
		normals2[i].clear();
	}
	normals2.clear();
	
	computedNormals = true;
}

Vec3f Terrain::get_normal(int x, int z) {
	if (!computedNormals) {
		compute_normals();
	}
	return normals[z][x];	
}

int Terrain::width() {
	return w;
}

int Terrain::length() {
	return l;
}

void Terrain::set_height(int x, int z, float y) {
	hs[z][x] = y;
	computedNormals = false;
}

float Terrain::get_height(int x, int z) {
	return hs[z][x];	
}