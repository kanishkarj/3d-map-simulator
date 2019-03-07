#pragma once

#include<bits/stdc++.h>
#include "vec3f.h"

using namespace std;

class Terrain {
	private:
		int w; //Width
		int l; //Length
		float** hs; //Heights
		vector<vector<Vec3f>> normals;
		bool computedNormals; //Whether normals is up-to-date
	public: 
		Terrain(const char*, float);
		~Terrain();
		Terrain* load_image(const char*, float);
		void computeNormals();
		Vec3f getNormal(int x, int z);
		// getters and setters
		int width();
		int height();
		void set_height(int x, int z, float y);
		float get_height(int x, int z);
};