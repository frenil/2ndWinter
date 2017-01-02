#include "stdafx.h"
#include "Player.h"
#include "Character.h"
CPlayer::CPlayer()
{
	player_state = 0;
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
	if (!onBlock) {
		player_state = 2;
	}
	else if (movevec.x != 0 || movevec.z != 0) {
		player_state = 1;
	}
	else player_state = 0;

	render.update_character(player_state);

	
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
		if (view == 0) {
			float rad = atan2f(movevec.z,
				movevec.x) * 180 / 3.14;
			glTranslatef(position.x, position.y-50, position.z);
			glRotatef( -rad, 0, 1, 0);
		}
		else {
			glTranslatef(position.x, position.y-50, 0);
			if (movevec.x == -1) {
				glRotatef(180, 0, 1, 0);
			}
		}
		glScalef(size.x/300, size.y / 425, size.z / 425);
		render.make_character();// glutSolidCube(1);
	}
	glPopMatrix();
}
