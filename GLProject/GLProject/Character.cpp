#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	player.mid_from_bottom = 175;
	player.mid_size = 50;
	player.leg_size = 100;  // 50ÀÇ 3/4 ÀÇ 4¹è
	player.foot_size = 25;  // 1/4
	player.leg_term = 25;
	player.original_mid = 200; //player.mid_from_bottom * 1.15;
	player.head_size = 100;
	player.arm_size = 50;
	player.noze_size = 20;
	player.eye_size = 20;
	player.beard_size = 50;
	player.mouse_size = 100;
}

void Character::update_character(int state)
{

	if (arm_right)
	{
		rotate_arm = (rotate_arm - 5) % 46;
	}
	else if (arm_left)
	{
		rotate_arm = (rotate_arm + 5) % 46;
	}

	if (leg_right)
	{
		rotate_leg = (rotate_leg - 5) % 46;
	}
	else if (leg_left)
	{
		rotate_leg = (rotate_leg + 5) % 46;
	}

	if (rotate_arm <= -45)
	{
		arm_left = true;
		arm_right = false;
	}
	else if (rotate_arm >= 45)
	{
		arm_right = true;
		arm_left = false;
	}

	if (rotate_leg <= -45)
	{
		leg_left = true;
		leg_right = false;
	}
	else if (rotate_leg >= 45)
	{
		leg_left = false;
		leg_right = true;
	}


	switch (state)
	{
	case 0:
		char_state = STATE::IDLE;
		break;
	case 1:
		char_state = STATE::RUN;
		break;
	case 2:
		char_state = STATE::JUMP;
		break;
	case 3:
		char_state = STATE::DIE_BRICK;
		break;
	case 4:
		char_state = STATE::DIE_MUSH;
		break;
	}
}

void Character::make_character()
{
	glShadeModel(GL_SMOOTH);
	{
		{
			//¸Ó¸®
			glPushMatrix();
			glColor3f(0.0, 1.0, 1.0);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size, 0.0);
			glScalef(1.25, 1.5, 1.5);
			glutSolidCube(player.head_size);
			glPopMatrix();

			//ÄÚ
			glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size, 0.0);
			glTranslatef(70, 0.0, 0.0);
			glutSolidSphere(player.noze_size, 30, 30);
			glPopMatrix();
			//

			//´«
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size + 2 * player.eye_size, 0.0);
			glTranslatef(50, 0.0, 0.0);
			glTranslatef(0.0, 0.0, player.eye_size * 2);
			glutSolidSphere(player.eye_size, 30, 30);
			glPopMatrix();
			glPushMatrix();

			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size + 2 * player.eye_size, 0.0);
			glTranslatef(50, 0.0, 0.0);
			glTranslatef(0.0, 0.0, -player.eye_size * 2);
			glutSolidSphere(player.eye_size, 30, 30);
			glPopMatrix();
			//

			//¼ö¿°
			glPushMatrix();
			glColor3f(0.60, 0.45, 0.12);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size - 25, 0.0);
			glTranslatef(50, 0.0, 0.0);
			glScalef(1.0, 0.15, 2.0);
			glutSolidCube(player.beard_size);
			glPopMatrix();
			//

			//ÀÔ
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(0.0, player.original_mid + player.mid_size + player.head_size - 50, 0.0);
			glTranslatef(50, 0.0, 0.0);
			glScalef(0.3, 0.2, 0.8);
			glutSolidCube(player.mouse_size);
			glPopMatrix();
		}

		//ÆÈ
		{
			glPushMatrix();
			{
				glColor3f(1.0, 1.0, 0.0);
				glTranslatef(0.0, player.original_mid, 0.0);
				glTranslatef(0.0, -player.arm_size / 3, 0.0);
				glTranslatef(0.0, 0.0, player.mid_size + player.arm_size / 3);

				if (char_state == 1)
				{
					glTranslatef(0.0, 75, 0.0); //ÆÈÅ©±â »çÀÌÁî / 2
					glRotatef(rotate_arm, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -75, 0.0);
				}
				else if (char_state == 2)
				{
					glTranslatef(0.0, 75, 0.0);
					glRotatef(-30, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -75, 0.0);
				}

				glScalef(0.5, 1.5, 0.3);
				glutSolidCube(2 * player.arm_size);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(1.0, 1.0, 0.0);
				glTranslatef(0.0, player.original_mid, 0.0);
				glTranslatef(0.0, -player.arm_size / 3, 0.0);
				glTranslatef(0.0, 0.0, -player.mid_size - player.arm_size / 3);

				if (char_state == 1)
				{
					glTranslatef(0.0, 75, 0.0);
					glRotatef(-rotate_arm, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -75, 0.0);
				}
				else if (char_state == 2)
				{
					glTranslatef(0.0, 75, 0.0);
					glRotatef(180, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -75, 0.0);
				}

				glScalef(0.5, 1.5, 0.3);
				glutSolidCube(2 * player.arm_size);
			}
			glPopMatrix();

		}

		//¸öÅë
		glPushMatrix();
		{
			glColor3f(1.0, 0.0, 0.0);

			glTranslatef(0.0, 1.15 * player.mid_from_bottom, 0.0);
			glScalef(1.0, 1.5, 1.0);

			//¾Õ¸é
			glBegin(GL_QUADS);
			glVertex3f(player.mid_size, player.mid_size, player.mid_size);	//¿ÞÂÊ»ó´Ü A
			glVertex3f(player.mid_size, -player.mid_size, player.mid_size);	//¿ÞÂÊÇÏ´Ü B
			glVertex3f(-player.mid_size, -player.mid_size, player.mid_size); //¿À¸¥ÇÏ´Ü C
			glVertex3f(-player.mid_size, player.mid_size, player.mid_size); //¿À¸¥»ó´Ü D
			glEnd();

			//µÞ¸é
			glBegin(GL_QUADS);
			glVertex3f(-player.mid_size, player.mid_size, -player.mid_size); //¿ÞÂÊ»ó´Ü µÞ D
			glVertex3f(-player.mid_size, -player.mid_size, -player.mid_size); //¿ÞÂÊÇÏ´Ü µÞ C
			glVertex3f(player.mid_size, -player.mid_size, -player.mid_size);	//¿À¸¥ÂÊÇÏ´Ü µÞ B
			glVertex3f(player.mid_size, player.mid_size, -player.mid_size);	//¿À¸¥ÂÊ»ó´Ü µÞ A
			glEnd();

			//¿Þ¸é
			glBegin(GL_QUADS);
			glVertex3f(-player.mid_size, player.mid_size, -player.mid_size); //D
			glVertex3f(-player.mid_size, -player.mid_size, -player.mid_size); //C
			glVertex3f(player.mid_size, -player.mid_size, player.mid_size);	//B
			glVertex3f(player.mid_size, player.mid_size, player.mid_size);	//A
			glEnd();

			//¿À¸¥¸é
			glBegin(GL_QUADS);
			glVertex3f(player.mid_size, player.mid_size, player.mid_size);	//D
			glVertex3f(player.mid_size, -player.mid_size, player.mid_size);	//C
			glVertex3f(-player.mid_size, -player.mid_size, -player.mid_size); //B
			glVertex3f(-player.mid_size, player.mid_size, -player.mid_size); //A
			glEnd();

			//¾Æ·§¸é
			glBegin(GL_QUADS);
			glVertex3f(player.mid_size, -player.mid_size, player.mid_size);	//B
			glVertex3f(player.mid_size, -player.mid_size, -player.mid_size); //A
			glVertex3f(-player.mid_size, -player.mid_size, -player.mid_size); //D
			glVertex3f(-player.mid_size, -player.mid_size, player.mid_size); //C
			glEnd();

			//À­¸é
			glBegin(GL_QUADS);
			glVertex3f(player.mid_size, player.mid_size, -player.mid_size);	//B
			glVertex3f(player.mid_size, player.mid_size, player.mid_size);	//A
			glVertex3f(-player.mid_size, player.mid_size, player.mid_size); //D
			glVertex3f(-player.mid_size, player.mid_size, -player.mid_size); //C
			glEnd();

		}
		glPopMatrix();

		//´Ù¸®,¹ß
		glPushMatrix();
		{
			{//´Ù¸®

				glColor3f(0.0, 0.0, 1.0);

				//----------------------------------------------------------¿À¸¥ÂÊ
				glPushMatrix();

				glTranslatef(0.0, player.mid_from_bottom, 0.0);

				glTranslatef(0.0, -2 * player.mid_size, 0.0);
				glTranslatef(0.0, 0.0, player.leg_term);

				if (char_state == 1)
				{
					glTranslatef(0.0, 50, 0.0);
					glRotatef(rotate_leg, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -50, 0.0);
				}
				else if (char_state == 2)
				{
					glTranslatef(0.0, 50, 0.0);
					glRotatef(80, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -50, 0.0);
				}

				glScalef(0.5, 1.0, 0.4);
				glutSolidCube(player.leg_size);

				glPopMatrix();

				//------------------------------------------------------------¿ÞÂÊ
				glPushMatrix();

				glTranslatef(0.0, player.mid_from_bottom, 0.0);

				glTranslatef(0.0, -2 * player.mid_size, 0.0);
				glTranslatef(0.0, 0.0, -player.leg_term);

				if (char_state == 1)
				{
					glTranslatef(0.0, 50, 0.0);
					glRotatef(-rotate_leg, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -50, 0.0);
				}
				else if (char_state == 2)
				{
					glTranslatef(0.0, 50, 0.0);
					glRotatef(-30, 0.0, 0.0, 1.0);
					glTranslatef(0.0, -50, 0.0);
				}

				glScalef(0.5, 1.0, 0.4);
				glutSolidCube(player.leg_size);

				glPopMatrix();
			}//´Ù¸®


			{//¹ß
				glColor3f(1.0, 1.0, 1.0);

				//----------------------------------------------------------¿À¸¥ÂÊ
				glPushMatrix();
				{
					glTranslatef(0.0, player.mid_from_bottom, 0.0);
					glTranslatef(0.0, -6.5 * player.foot_size, 0.0);
					glTranslatef(player.foot_size, 0.0, 0.0);
					glTranslatef(0.0, 0.0, player.leg_term);

					if (char_state == 1) //°È±â
					{
						glTranslatef(0.0, 87.5, 0.0);
						glTranslatef(-player.foot_size, 0.0, 0.0);
						glRotatef(rotate_leg, 0.0, 0.0, 1.0);
						glTranslatef(player.foot_size, 0.0, 0.0);
						glTranslatef(0.0, -87.5, 0.0);
					}
					else if (char_state == 2)
					{
						glTranslatef(0.0, 87.5, 0.0);
						glTranslatef(-player.foot_size, 0.0, 0.0);
						glRotatef(80, 0.0, 0.0, 1.0);
						glTranslatef(player.foot_size, 0.0, 0.0);
						glTranslatef(0.0, -87.5, 0.0);
					}

					glScalef(1.0, 0.25, 0.4);
					glutSolidCube(player.leg_size);

				}
				glPopMatrix();

				glColor3f(1.0, 1.0, 1.0);

				//----------------------------------------------------------¿ÞÂÊ
				glPushMatrix();
				{
					glTranslatef(0.0, player.mid_from_bottom, 0.0);
					glTranslatef(0.0, -6.5 * player.foot_size, 0.0);
					glTranslatef(player.foot_size, 0.0, 0.0);
					glTranslatef(0.0, 0.0, -player.leg_term);

					if (char_state == 1)
					{
						glTranslatef(0.0, 87.5, 0.0);
						glTranslatef(-player.foot_size, 0.0, 0.0);
						glRotatef(-rotate_leg, 0.0, 0.0, 1.0);
						glTranslatef(player.foot_size, 0.0, 0.0);
						glTranslatef(0.0, -87.5, 0.0);
					}
					else if (char_state == 2)
					{
						glTranslatef(0.0, 87.5, 0.0);
						glTranslatef(-player.foot_size, 0.0, 0.0);
						glRotatef(-30, 0.0, 0.0, 1.0);
						glTranslatef(player.foot_size, 0.0, 0.0);
						glTranslatef(0.0, -87.5, 0.0);
					}

					glScalef(1.0, 0.25, 0.4);
					glutSolidCube(player.leg_size);
				}
				glPopMatrix();

			}//¹ß

		}
		glPopMatrix();
		//

	}

}

CharPos Character::Get_CharPos() const
{
	return m_char_pos;
}

void Character::Set_CharPos(float m_x, float m_y, float m_z)
{
	m_char_pos.x += m_x;
	m_char_pos.y += m_y;
	m_char_pos.z += m_z;
}

Character::~Character()
{
}
