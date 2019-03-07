#pragma once

#include<bits/stdc++.h>
#include <3d_map_simulator/vec3f.h>

using namespace std;

class Terrain {
	private:
		int w; //Width
		int l; //Length
		vector<vector<float>> hs; //Heights
		vector<vector<Vec3f>> normals;
		bool computedNormals; //Whether normals is up-to-date
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