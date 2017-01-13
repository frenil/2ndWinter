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

void CPlayer::Update()
{
	if (!isDie)
	{
		if (!onBlock) {
			position.y += Yspeed;
			Yspeed -= 1;
		}
		else {
			Yspeed = 0;
		}
		preposition = position;
		position += Speed*movevec;
		if (position.y <= -300)
		{
			isDie = true;
		}
	}
	else if (isDie) {
		isDie = false;
		Yspeed = 0;
		position =  SavePos* 100;
	}
	if (0 != movevec.x || 0 != movevec.z) {

		glPushMatrix();
		{
			glLoadIdentity();
			glRotatef(-5,  0,  movevec.z,-movevec.x );
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

void CPlayer::RenderDie()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
	}
	glPopMatrix();
}

void CPlayer::Render(int view)
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.37f, 0.37f);
		glTranslatef(position.x, position.y, position.z);
		glScalef(size.x, size.y , size.z );
		//glutSolidSphere(0.5, 18, 18);
		glColor3f(1.f, 0.f, 0.f);
		glMultMatrixf(Mat);
		glutWireSphere(0.5,18,18);
	}
	glPopMatrix();
}
