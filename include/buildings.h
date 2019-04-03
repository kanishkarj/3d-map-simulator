/*
this header file consists of all buildings
*/
#include <bits/stdc++.h>
#include "../include/vec3f.h"

using namespace std;

vector<Vec3f> construct_building(float l, float b, float h) {
	vector<Vec3f> t(8);
	t[0] = Vec3f(0,0,0);
	t[1] = Vec3f(b,0,0);
	t[2] = Vec3f(b,h,0);
	t[3] = Vec3f(0,h,0);
	t[4] = Vec3f(0,h,l);
	t[5] = Vec3f(0,0,l);
	t[6] = Vec3f(b,0,l);
	t[7] = Vec3f(b,h,l);
	return t;
}

auto buliding_struct_1_l = construct_building(18.75,18.75,75);
auto buliding_struct_2_l = construct_building(18.75,25,75);
auto buliding_struct_3_l = construct_building(25,18.75,75);
auto buliding_struct_1_md = construct_building(18.75,18.75,50);
auto buliding_struct_2_md = construct_building(18.75,25,50);
auto buliding_struct_3_md = construct_building(25,18.75,50);
auto buliding_struct_1_sm = construct_building(18.75,18.75,25);
auto buliding_struct_2_sm = construct_building(18.75,25,25);
auto buliding_struct_3_sm = construct_building(25,18.75,25);
auto sky_coord = construct_building(500,500,500);
