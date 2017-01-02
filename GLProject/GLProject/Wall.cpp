#include "stdafx.h"
#include "Wall.h"



CWall::CWall()
{
}


CWall::~CWall()
{
}

void CWall::Update()
{
	if (collide) {
		vertex.y += 10;
		if (vertex.y >= position.y) {
			vertex.y = position.y;
			collide = false;
		}
	}
	else {
		vertex.y -= 20;
	}
}

void CWall::SetWallPos(Vec3f a)
{
	position.x =vertex.x = a.x * 100;
	position.y =vertex.y = a.y * 100;
	position.z =vertex.z = a.z * 100;
}

void CWall::DrawWall()
{
	glPushMatrix();
	{
		glTranslatef(vertex.x, vertex.y, vertex.z);
		glScalef(size.x, size.y, size.z);
		render.DrawBrick_FUNC();
	}
	glPopMatrix();
}
