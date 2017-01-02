#include "stdafx.h"
#include "block.h"



CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::SetBlockPos(Vec3f input)
{
	vertex = 100 * input;
}


void CBlock::DrawBolck()
{
	GLUquadricObj* cyl;
	cyl = gluNewQuadric();
	glPushMatrix();
	{		glColor4f(1,1,1,1);

			glTranslatef(vertex.x, vertex.y, vertex.z);
			glScalef(size.x, size.y, size.z);
			render.DrawBrick_FUNC();

		}
		glPopMatrix();
}

