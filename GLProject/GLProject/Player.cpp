#include "stdafx.h"
#include "Player.h"
#include "Character.h"
CPlayer::CPlayer()
{
	player_state = 0;
	size = {100, 100, 100};
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
		glTranslatef(position.x, position.y, position.z);
		glScalef(size.x, size.y , size.z );
		glutSolidCube(1);
	}
	glPopMatrix();
}
