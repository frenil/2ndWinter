#pragma once
#include <vector>
#include <gl/glut.h>
#include "GlobalDefine.h"

using namespace std;

struct weather_pos
{
	float x;
	float y;
	float z;
	float speed;
};


class CWeather
{
private:
	weather_pos wpos;
	vector<weather_pos> we_vec;
	bool start_flag;

public:
	CWeather();
	void init_weather(bool weather_flag);
	void draw_weather(int select_weather);
	void update_weather(int select_weather);
	~CWeather();
};

