#include "stdafx.h"
#include "Stage.h"



CStage::CStage()
{
}


CStage::~CStage()
{
}

void CStage::DrawDestinate()
{
	glPushMatrix();
	{
		glColor3f(0, 0, 1);
		glTranslatef(Destinate.x, Destinate.y, Destinate.z);
		glScalef(DSize.x, DSize.y, DSize.z);
		glutSolidCube(1);
	}
	glPopMatrix();
}


