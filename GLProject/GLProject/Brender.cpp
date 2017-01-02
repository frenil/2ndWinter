#include "stdafx.h"
#include "Brender.h"

Vec3D<float> CBrender::Calculate_Normal(CKH_NORM_DATA fdata, CKH_NORM_DATA ldata)
{
	ckh_vec3d.x = fdata.x;
	ckh_vec3d.y = fdata.y;
	ckh_vec3d.z = fdata.z;

	ckh_other_vec3d.x = ldata.x;
	ckh_other_vec3d.y = ldata.y;
	ckh_other_vec3d.z = ldata.z;

	return Normalize(Cross(ckh_vec3d, ckh_other_vec3d));
}


void CBrender::MakeBrickTexture_FUNC()
{
	glGenTextures(m_texture_num, m_textures);
	//----------------------------------------------------------------------------------------------------------------- 이걸 여러번 반복 ->텍스처가 여러개일시
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	m_TexBits = get_load->ckh_LoadBitmap("wall.bmp", &m_info);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture_size, m_texture_size, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//------------------------------------------------------------------------------------------------------------------
}

void CBrender::MakeNORMAL_FUNC()
{
	//윗면
	Fdata[0].x = 0;
	Fdata[0].y = 0;
	Fdata[0].z = 2 * m_brick_size;

	Ldata[0].x = 2 * m_brick_size;
	Ldata[0].y = 0;
	Ldata[0].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[0], Ldata[0]).x,
		this->Calculate_Normal(Fdata[0], Ldata[0]).y,
		this->Calculate_Normal(Fdata[0], Ldata[0]).z);

	//앞면
	Fdata[1].x = 0;
	Fdata[1].y = -2 * m_brick_size;
	Fdata[1].z = 0;

	Ldata[1].x = 2 * m_brick_size;
	Ldata[1].y = 0;
	Ldata[1].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[1], Ldata[1]).x,
		this->Calculate_Normal(Fdata[1], Ldata[1]).y,
		this->Calculate_Normal(Fdata[1], Ldata[1]).z);

	//아랫면
	Fdata[2].x = 0;
	Fdata[2].y = 0;
	Fdata[2].z = -2 * m_brick_size;

	Ldata[2].x = 2 * m_brick_size;
	Ldata[2].y = 0;
	Ldata[2].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[2], Ldata[2]).x,
		this->Calculate_Normal(Fdata[2], Ldata[2]).y,
		this->Calculate_Normal(Fdata[2], Ldata[2]).z);

	//뒷면
	Fdata[3].x = 0;
	Fdata[3].y = -2 * m_brick_size;
	Fdata[3].z = 0;

	Ldata[3].x = -2 * m_brick_size;
	Ldata[3].y = 0;
	Ldata[3].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[3], Ldata[3]).x,
		this->Calculate_Normal(Fdata[3], Ldata[3]).y,
		this->Calculate_Normal(Fdata[3], Ldata[3]).z);

	//왼쪽면
	Fdata[4].x = 0;
	Fdata[4].y = -2 * m_brick_size;
	Fdata[4].z = 0;

	Ldata[4].x = 0;
	Ldata[4].y = 0;
	Ldata[4].z = 2 * m_brick_size;

	glNormal3f(
		this->Calculate_Normal(Fdata[4], Ldata[4]).x,
		this->Calculate_Normal(Fdata[4], Ldata[4]).y,
		this->Calculate_Normal(Fdata[4], Ldata[4]).z);

	//오른쪽면
	Fdata[5].x = 0;
	Fdata[5].y = -2 * m_brick_size;
	Fdata[5].z = 0;

	Ldata[5].x = 0;
	Ldata[5].y = 0;
	Ldata[5].z = -2 * m_brick_size;

	glNormal3f(
		this->Calculate_Normal(Fdata[5], Ldata[5]).x,
		this->Calculate_Normal(Fdata[5], Ldata[5]).y,
		this->Calculate_Normal(Fdata[5], Ldata[5]).z);
}

void CBrender::DrawBrick_FUNC()
{
	glEnable(GL_TEXTURE_2D);

	if (show_once)
	{
		this->MakeBrickTexture_FUNC();
		show_once = false;
	}
	//this->MakeNORMAL_FUNC();


	glBindTexture(GL_TEXTURE_2D, m_textures[0]);

	glColor3f(1, 1, 1);

	//윗면
	Fdata[0].x = 0;
	Fdata[0].y = 0;
	Fdata[0].z = 2 * m_brick_size;

	Ldata[0].x = 2 * m_brick_size;
	Ldata[0].y = 0;
	Ldata[0].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[0], Ldata[0]).x,
		this->Calculate_Normal(Fdata[0], Ldata[0]).y,
		this->Calculate_Normal(Fdata[0], Ldata[0]).z);


	//윗면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-m_brick_size, m_brick_size, -m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-m_brick_size, m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(m_brick_size, m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(m_brick_size, m_brick_size, -m_brick_size);
	glEnd();

	//앞면
	Fdata[1].x = 0;
	Fdata[1].y = -2 * m_brick_size;
	Fdata[1].z = 0;

	Ldata[1].x = 2 * m_brick_size;
	Ldata[1].y = 0;
	Ldata[1].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[1], Ldata[1]).x,
		this->Calculate_Normal(Fdata[1], Ldata[1]).y,
		this->Calculate_Normal(Fdata[1], Ldata[1]).z);

	//앞면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-m_brick_size, m_brick_size, m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-m_brick_size, -m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(m_brick_size, -m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(m_brick_size, m_brick_size, m_brick_size);
	glEnd();



	//아랫면
	Fdata[2].x = 0;
	Fdata[2].y = 0;
	Fdata[2].z = -2 * m_brick_size;

	Ldata[2].x = 2 * m_brick_size;
	Ldata[2].y = 0;
	Ldata[2].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[2], Ldata[2]).x,
		this->Calculate_Normal(Fdata[2], Ldata[2]).y,
		this->Calculate_Normal(Fdata[2], Ldata[2]).z);


	//아랫면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-m_brick_size, -m_brick_size, m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(m_brick_size, -m_brick_size, m_brick_size);
	glEnd();

	//뒷면
	Fdata[3].x = 0;
	Fdata[3].y = -2 * m_brick_size;
	Fdata[3].z = 0;

	Ldata[3].x = -2 * m_brick_size;
	Ldata[3].y = 0;
	Ldata[3].z = 0;

	glNormal3f(
		this->Calculate_Normal(Fdata[3], Ldata[3]).x,
		this->Calculate_Normal(Fdata[3], Ldata[3]).y,
		this->Calculate_Normal(Fdata[3], Ldata[3]).z);

	//뒷면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(m_brick_size, m_brick_size, -m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-m_brick_size, m_brick_size, -m_brick_size);
	glEnd();

	//왼쪽면
	Fdata[4].x = 0;
	Fdata[4].y = -2 * m_brick_size;
	Fdata[4].z = 0;

	Ldata[4].x = 0;
	Ldata[4].y = 0;
	Ldata[4].z = 2 * m_brick_size;

	glNormal3f(
		this->Calculate_Normal(Fdata[4], Ldata[4]).x,
		this->Calculate_Normal(Fdata[4], Ldata[4]).y,
		this->Calculate_Normal(Fdata[4], Ldata[4]).z);


	//왼쪽면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-m_brick_size, m_brick_size, -m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-m_brick_size, -m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-m_brick_size, m_brick_size, m_brick_size);
	glEnd();

	//오른쪽면
	Fdata[5].x = 0;
	Fdata[5].y = -2 * m_brick_size;
	Fdata[5].z = 0;

	Ldata[5].x = 0;
	Ldata[5].y = 0;
	Ldata[5].z = -2 * m_brick_size;

	glNormal3f(
		this->Calculate_Normal(Fdata[5], Ldata[5]).x,
		this->Calculate_Normal(Fdata[5], Ldata[5]).y,
		this->Calculate_Normal(Fdata[5], Ldata[5]).z);

	//오른쪽면
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(m_brick_size, m_brick_size, m_brick_size);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(m_brick_size, -m_brick_size, m_brick_size);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(m_brick_size, -m_brick_size, -m_brick_size);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(m_brick_size, m_brick_size, -m_brick_size);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}




CBrender::CBrender()
{
}


CBrender::~CBrender()
{
}
