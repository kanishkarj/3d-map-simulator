#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include<bits/stdc++.h>
#include <GL/glut.h>
#include "vec3f.h"

using namespace std;

class Terrain {
	private:
		int w; 
		int l; 
		vector<vector<float>> hs; 
		vector<vector<Vec3f>> normals;
		bool computedNormals; 
	public: 
		Terrain(const char*, float);
		~Terrain();
		void load_image(const char*, float);
		void compute_normals();
		Vec3f get_normal(int x, int z);
		// getters and setters
		int width();
		int length();
		void set_height(int x, int z, float y);
		float get_height(int x, int z);
};

#endif