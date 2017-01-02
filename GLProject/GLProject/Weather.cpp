#include "stdafx.h"
#include "Weather.h"


CWeather::CWeather()
{
}

void CWeather::init_weather(bool weather_flag)
{
	if (weather_flag)
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			wpos.x = rand() % 2000 - 1000;
			wpos.y = rand() % 100 + 700;
			wpos.z = rand() % 2000 - 1000;
			wpos.speed = rand() % 19 + 1;

			we_vec.push_back(wpos);
		}
	}
	else
	{
		if (!we_vec.empty())
			we_vec.clear();

		for (int i = 0; i < MAX_NUM; ++i)
		{
			wpos.x = rand() % 2000 - 1000;
			wpos.y = rand() % 100 + 700;
			wpos.z = rand() % 2000 - 1000;
			wpos.speed = rand() % 19 + 1;

			we_vec.push_back(wpos);
		}
	}
}

void CWeather::update_weather(int select_weather)
{
	if (select_weather == 1)
	{
		if (!we_vec.empty())
		{
			we_vec.clear();
		}
	}
	if (select_weather == 2)
	{
		if (!we_vec.empty())
		{
			for (int i = 0; i < we_vec.size(); ++i)
			{
				if (we_vec[i].y < 0)
					we_vec[i].y = rand() % 100 + 700;
				else
					we_vec[i].y -= we_vec[i].speed;
			}
		}
	}
	else if (select_weather == 3)
	{
		if (!we_vec.empty())
		{
			for (int i = 0; i < we_vec.size(); ++i)
			{
				if (we_vec[i].y < 0)
					we_vec[i].y = rand() % 100 + 700;
				else
					we_vec[i].y -= we_vec[i].speed;
			}
		}
	}
}

void CWeather::draw_weather(int select_weather)
{
	//¸¼À½
	if (select_weather == 1)
	{

	}
	else if (select_weather == 2)
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);

			glTranslatef(we_vec[i].x, 0.0, 0.0);
			glTranslatef(0.0, we_vec[i].y, 0.0);
			glTranslatef(0.0, 0.0, we_vec[i].z);

			glutSolidSphere(1, 10, 10);
			glPopMatrix();
		}
	}
	else if (select_weather == 3)
	{
		for (int i = 0; i < MAX_NUM; ++i)
		{
			glPushMatrix();
			glColor3f(0.8, 0.8, 1);

			glTranslatef(we_vec[i].x, 0.0, 0.0);
			glTranslatef(0.0, we_vec[i].y, 0.0);
			glTranslatef(0.0, 0.0, we_vec[i].z);

			glScalef(0.5, 20.0, 0.5);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
}

CWeather::~CWeather()
{
}
