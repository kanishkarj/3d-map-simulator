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

vector<vector<float>> building_coord = {	
    {12.5,12.5,18.75,18.75},
	{37.5,12.5,25,18.75},
	{67.625,12.5,18.75,18.75},
	{95,12.5,18.75,25},
	{130,12.5,18.75,25},
	{162.5,12.5,25,18.75},
	{193.75,12.5,25,18.75},
	{218.75,12.5,18.75,18.75},
	{255,12.5,25,18.75},
	{12.5,255,25,18.75},
	{37.5,252.4,18.75,18.75},
	{67.625,252.4,18.75,25},
	{95,255,18.75,18.75},
	{130,257.4,25,18.75},
	{155,255,18.75,25},
	{193.75,252.4,18.75,18.75},
	{218.75,255,25,18.75},
	{255,252.4,25,18.75},
	{197,124,30,30},
	{74,190,30,30},
	{154,120,30,20},
	{197,197,30,20},
	{84,145,20,30},
	{198,80,20,30},
	{198,55,20,30},
	{82,55,20,30},
	{69,82,18.75,18.75},
	{69,119,18.75,18.75},
	{129,142,18.75,18.75},
	{220,177,18.75,18.75},
	{133,190,30,30},
	{129,74,30,20},
	{148,51,20,30}
};

auto sky_coord = construct_building(500,500,500);

auto buliding_struct_1_l = construct_building(18.75,18.75,75);
auto buliding_struct_2_l = construct_building(18.75,25,75);
auto buliding_struct_3_l = construct_building(25,18.75,75);
auto buliding_struct_1_md = construct_building(18.75,18.75,50);
auto buliding_struct_2_md = construct_building(18.75,25,50);
auto buliding_struct_3_md = construct_building(25,18.75,50);
auto buliding_struct_1_sm = construct_building(18.75,18.75,25);
auto buliding_struct_2_sm = construct_building(18.75,25,25);
auto buliding_struct_3_sm = construct_building(25,18.75,25);

auto buliding_struct_4_xsm = construct_building(30,30,15);
auto buliding_struct_5_xsm = construct_building(30,20,15);
auto buliding_struct_6_xsm = construct_building(20,30,15);

auto buliding_struct_4_sm = construct_building(30,30,25);
auto buliding_struct_5_sm = construct_building(30,20,25);
auto buliding_struct_6_sm = construct_building(20,30,25);

auto buliding_struct_4_md = construct_building(30,30,50);
auto buliding_struct_5_md = construct_building(30,20,50);
auto buliding_struct_6_md = construct_building(20,30,50);
