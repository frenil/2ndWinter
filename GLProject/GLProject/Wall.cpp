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
	position.x = vertex.x = a.x * 100;
	position.y = vertex.y = a.y * 100;
	position.z = vertex.z = a.z * 100;
}

void CWall::DrawWall(CTextureLibraray m_Wall)
{
	glPushMatrix();
	{

		CTextureLibraray::UsingTexture2D();
		{
			glColor4f(1, 1, 1, 1);
			m_Wall.LoadTexture(0);

			DrawQube(vertex, size);
			
			m_Wall.DisableTexture(0);
		}
		CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
}
