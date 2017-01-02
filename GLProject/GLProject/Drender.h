#pragma once
#include "stdafx.h"

class CExitCube
{
private:
	int m_floatsize = 25;
	int m_big_cubesize = 200;
	int m_small_cubesize = 120;
	int m_rotate_angle = 0;

	float m_updown = 0.f;
	bool m_IsUp = true;
	bool m_IsDown = false;
	int m_movesize = 2;
public:
	CExitCube();
	void Update_Exitcube();
	void Draw_Exitcube();
	~CExitCube();
};

