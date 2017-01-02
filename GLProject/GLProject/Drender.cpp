#include "stdafx.h"
#include "Drender.h"

CExitCube::CExitCube()
{
}

void CExitCube::Update_Exitcube()
{
	m_rotate_angle = (m_rotate_angle + 1) % 360;

	if (m_IsUp) m_updown += m_movesize;
	else if (m_IsDown) m_updown -= m_movesize;

	if (m_updown >= 100)
	{
		m_IsDown = true;
		m_IsUp = false;
	}

	if (m_updown <= 0)
	{
		m_IsUp = true;
		m_IsDown = false;
	}
}

void CExitCube::Draw_Exitcube()
{

	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTranslatef(0.0, m_floatsize + m_big_cubesize / 2, 0.0);

		glTranslatef(0.0, m_updown, 0.0);

		glPushMatrix();
		glColor4f(0.0, 0.0, 0.8, 0.8);

		glRotatef(45, 0.0, 0.0, 1.0);
		glRotatef(45, 1.0, 0.0, 0.0);

		glRotatef(m_rotate_angle, 0.0, 0.0, 1.0);
		glutSolidCube(m_small_cubesize);
		glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 0.5);
		glutSolidCube(m_big_cubesize);
		glPopMatrix();


		glPopMatrix();
		glDisable(GL_BLEND);
	}
	glPopMatrix();

}


CExitCube::~CExitCube()
{
}
