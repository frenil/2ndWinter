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
			glTranslatef(vertex.x, vertex.y, vertex.z);
			glRotatef(90, 1, 0, 0);
			glutSolidTorus(10, 40, 12, 12);
			glPushMatrix();
			{
				glTranslatef(0, 0, -40);
				glutSolidTorus(10, 40, 12, 12);

			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, 0, 40);
				glutSolidTorus(10, 40, 12, 12);

			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}

