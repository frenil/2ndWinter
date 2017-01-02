#include "stdafx.h"
#include "Mush.h"



CMush::CMush()
{
}


CMush::~CMush()
{
}

void CMush::Update()
{
	render.UpdateMush_FUNC();
}

void CMush::SetMushPos(Vec3f a)
{
	position = vertex = 100*a;
}

void CMush::DrawMush()
{
	if (!isDie) {
		glPushMatrix();
		{
			glColor3f(1, 1, 0);
			glTranslatef(vertex.x, vertex.y-50, vertex.z);
			glScalef(size.x/300, size.y/400, size.z/300);
			render.DrawMushroom_FUNC();
		}
		glPopMatrix();
	}
}

