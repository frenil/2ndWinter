#include "stdafx.h"
#include "Player.h"
CPlayer::CPlayer()
{
	size = {100, 100, 100};
	movevec = { 0,0,0 };
	rotate_rad = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				Mat[i + (j * 4)] = 1.f;
			else 
				Mat[i + (j * 4)] = 0.f;
		}
	}
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(float deltatime)
{
	if (!isDie)
	{
		if (!onBlock) {
			position.y += Yspeed *deltatime/25;
			Yspeed -= 1;
		}
		else {
			Yspeed = 0;
		}
		preposition = position;
		position += (Speed*deltatime/25)*movevec;
		angle_annie = (angle_annie + angle_speed) / 50 % 360;
		if (position.y <= -300)
		{
			isDie = true;
		}
	}
	else if (isDie) {
		isDie = false;
		Yspeed = 0;
		position =  SavePos* 100;
		init();
	}
	if (0 != movevec.x || 0 != movevec.z) {

		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(-5*deltatime / 10, -movevec.z,0  ,movevec.x );
			glMultMatrixf(Mat);
			glGetFloatv(GL_MODELVIEW_MATRIX, Mat);
		}
		glPopMatrix();
	}
}

void CPlayer::Jump()
{
	
	if (jump_count==0) {
		Yspeed = 25; 
		onBlock = false; 
		position.y += 1;
	}
}

void CPlayer::init()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				Mat[i + (j * 4)] = 1.f;
			else
				Mat[i + (j * 4)] = 0.f;
		}
	}
	movevec = { 0, 0, 0 };
}

void CPlayer::RenderDie()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
	}
	glPopMatrix();
}

void CPlayer::Render(int view)
{	glPushMatrix();
	{
		glColor3f(1.f, 0.37f, 0.37f);
		glTranslatef(position.x, position.y-15, position.z);
		glutSolidSphere(35, 18, 18);
		glColor3f(1.f, 0.f, 0.f);
		glMultMatrixf(Mat);
		glutWireSphere(35,18,18);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(position.x, position.y-15, position.z);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.f, 1.f, 1.f);
		glutSolidTorus(8, 32, 8, 18);
		
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(position.x, position.y-15, position.z);
		glRotatef(angle_annie, 0, 1, 0);
		for (int i = 0; i < 9; i++) {
			glPushMatrix();
			{
				glRotatef(40*i, 0, 1, 0);
				glTranslatef(38, 0, 0);
				glColor3f(1.f, 1.f, 1.f);
				glutSolidCube(15);
				glColor3f(0.f, 1.f, 0.f);
				glutWireCube(15);
			}
			glPopMatrix();
		}glColor3f(1.f, 1.f, 1.f);
	}
	glPopMatrix();
}
