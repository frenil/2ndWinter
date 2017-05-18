#pragma once

#include <gl/glut.h>

#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <list>
#include <chrono>

#include <algorithm>
#include <Windows.h>
#include "Vector3D.h"

using namespace std;
using std::ifstream;
using std::ofstream;

enum {PLAY,REPLAY};
enum {SUP,SDOWN,SLEFT,SRIGHT,SSPACE,SZ};
enum {PDOWN, INIT,PUP};
enum {KEYSPACE,KEYZ };
enum {MUP,MDOWN,MLEFT,MRIGHT};
enum { UP = 1, DOWN = -1, ZSIDE = 2, XSIDE = 3 };
struct COLLIDETYPE {
	bool UP;
	bool DOWN;
	bool X;
	bool Z;
};
enum class GLKeyStateCombine : long
{
	  LBUTTONDOWN	= ((long(GLUT_LEFT_BUTTON)	<< 8) + GLUT_DOWN)
	, RBUTTONDOWN	= ((long(GLUT_RIGHT_BUTTON)	<< 8) + GLUT_DOWN)
	, LBUTTONUP		= ((long(GLUT_LEFT_BUTTON)	<< 8) + GLUT_UP)
	, RBUTTONUP		= ((long(GLUT_RIGHT_BUTTON)	<< 8) + GLUT_UP)
};

constexpr inline GLKeyStateCombine GetMouseState(int button, int state) noexcept { return GLKeyStateCombine((long(button) << 8) + long(state)); }

#define STR_TITLE_CAPTION	"Tutering Sample_2016_2"

#define STARTPOSITION_X		100
#define STARTPOSITION_Y		100

#define CLIENTWIDTH			800
#define CLIENTHEIGHT		600

#define GAMEFPS				1000 / 60

#ifndef PI
#define PI					3.141592f
#endif // !PI

constexpr inline float DegreeToRadian(float degree) noexcept { return degree * PI * 0.005555; }

inline Vec3f Nomalize(Vec3f vec) 
{
	if(0==vec.x && 0 == vec.y&&0 == vec.z)
		return vec;
	else return vec *(1 / (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)))); 
}

inline void DrawRectangle(float x, float y, float scale)
{
	glBegin(GL_POLYGON);
	{
		glVertex2d(x - scale, y + scale);
		glVertex2d(x + scale, y + scale);
		glVertex2d(x + scale, y - scale);
		glVertex2d(x - scale, y - scale);
	}
	glEnd();
}

inline void DrawCircle(float x, float y, float scale, int detail)
{
	assert(!(detail < 4) && "��� 4�� �̻��� �������� �������մϴ�!");

	float IncreaseAngle = 360.f / static_cast<float>(detail);

	glBegin(GL_POLYGON);
	{
		for (float angle = 0; angle < 360; angle += IncreaseAngle)
			glVertex2f(	  x + (cos(DegreeToRadian(angle)) * scale)
						, y + (sin(DegreeToRadian(angle)) * scale)
			);
	}
	glEnd();
}


inline void DrawQuad(const Vec3f& ptPosition, float fScale, bool isXY = false) {
	glPushMatrix();
	{
		glTranslatef(ptPosition.x, ptPosition.y, ptPosition.z);
		float fx = fScale *0.5f;
		float fy = (isXY) ? fScale *0.5f : 0;
		float fz = (isXY) ? 0 : fScale * 0.5f;
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, +fy, -fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, +fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, -fy, +fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, +fy, -fz);

		}
		glEnd();
	}
	glPopMatrix();
}

inline void DrawQube(const Vec3f& ptPosition, Vec3f fScale) {
	glPushMatrix();
	{
		glTranslatef(ptPosition.x, ptPosition.y, ptPosition.z);
		float fx = fScale.x *0.5f;
		float fy = fScale.y *0.5f;
		float fz = fScale.z * 0.5f;
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, +fy, -fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, -fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, -fy, -fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, +fy, -fz);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, +fy, fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, -fy, fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, +fy, fz);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, -fy, +fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, -fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, -fy, -fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, -fy, +fz);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, +fy, +fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, +fy, -fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, +fy, -fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, +fy, +fz);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(+fx, -fy, +fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(+fx, -fy, -fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+fx, +fy, -fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(+fx, +fy, +fz);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, +1.0f);
			glVertex3f(-fx, -fy, +fz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-fx, -fy, -fz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-fx, +fy, -fz);
			glTexCoord2f(1.0f, +1.0f);
			glVertex3f(-fx, +fy, +fz);
		}
		glEnd();
	}
	glPopMatrix();
}