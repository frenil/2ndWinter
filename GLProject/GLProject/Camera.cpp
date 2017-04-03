#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

Vec3f CCamera::GetLookVector() const
{
	return Normalize(Vec3f{
	 cos(DegreeToRadian(m_ptDelta.x))
	, tan(DegreeToRadian(m_ptDelta.y))
	, sin(DegreeToRadian(m_ptDelta.x))
	});
}

void CCamera::SetView(int view,Vec3f At)
{
 	if (view == 0) {//3Â÷¿ø
		SetDelta(180, 30);
		SetZoom(250);
		At.y += 50;
		Setposition(At);
		LookAt();
	}
	else if (view == 1) {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-500+At.x, At.x+ 500, -80, 920, -500, 10000);
		glMatrixMode(GL_MODELVIEW);

	}
}

void CCamera::LookAt()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.f, m_faspect, 100.f, 100000.f);
	auto eye = m_ptPosition + GetLookVector() *m_fZoom;
	gluLookAt(eye.x, eye.y, eye.z,
		m_ptPosition.x, m_ptPosition.y, m_ptPosition.z,
		0, 1, 0
	);
	glMatrixMode(GL_MODELVIEW);

}

void CCamera::SetTilte()
{
	m_fZoom = 1.f;
	m_ptDelta.x = 90;
	m_ptDelta.y = 0;
	m_faspect =  1.f;
	LookAt();
}
