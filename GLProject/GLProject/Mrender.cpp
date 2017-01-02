#include "stdafx.h"
#include "Mrender.h"


CMonster::CMonster()
{
	//monster_getLoad = new CGetTexture();
	//monster_getNorm = new CGetNormal();
}

void CMonster::UpdateMush_FUNC()
{
	if (!Limit_scale_x)
		scale_for_x += 0.01;
	else
		scale_for_x -= 0.01;

	if (scale_for_x >= 2.0)
		Limit_scale_x = true;

	if (scale_for_x <= 1.0)
		Limit_scale_x = false;

	if (!Limit_scale_y)
		scale_for_y -= 0.01;
	else
		scale_for_y += 0.01;

	if (scale_for_y >= 1.0)
		Limit_scale_y = false;

	if (scale_for_y <= 0.5)
		Limit_scale_y = true;

}


Vec3D<float> CMonster::Calculate_Normal(CKH_NORM_DATA fdata, CKH_NORM_DATA ldata)
{
	ckh_vec3d.x = fdata.x;
	ckh_vec3d.y = fdata.y;
	ckh_vec3d.z = fdata.z;

	ckh_other_vec3d.x = ldata.x;
	ckh_other_vec3d.y = ldata.y;
	ckh_other_vec3d.z = ldata.z;

	return Normalize(Cross(ckh_vec3d, ckh_other_vec3d));
}

void CMonster::MakeMushroomTexture_FUNC()
{
	glGenTextures(m_texture_num, m_textures);
	//----------------------------------------------------------------------------------------------------------------- 이걸 여러번 반복 ->텍스처가 여러개일시
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	m_TexBits = monster_getLoad->ckh_LoadBitmap("Mushroom_head.bmp", &m_info);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture_size, m_texture_size, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------------------- 이걸 여러번 반복 ->텍스처가 여러개일시
	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	m_TexBits = monster_getLoad->ckh_LoadBitmap("Mushroom_body.bmp", &m_info);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture_size, m_texture_size, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//------------------------------------------------------------------------------------------------------------------
}

void CMonster::DrawMushroom_FUNC()
{
	glEnable(GL_TEXTURE_2D);

	if (show_once)
	{
		this->MakeMushroomTexture_FUNC();
		show_once = false;
	}

	glPushMatrix();
	{
		glScalef(scale_for_x, scale_for_y, 1.0);
		glPushMatrix();
		{
			glTranslatef(0.0, m_mushroombody_rad + m_mushroomhead_size, 0.0);

			glBindTexture(GL_TEXTURE_2D, m_textures[0]);

			//노멀벡터적용

			glColor3f(1.f, 0.f, 0.f);
			//앞면
			Fdata[0].x = -m_mushroomhead_size;
			Fdata[0].y = -2 * m_mushroomhead_size;
			Fdata[0].z = m_mushroomhead_size;

			Ldata[0].x = m_mushroomhead_size;
			Ldata[0].y = -2 * m_mushroomhead_size;
			Ldata[0].z = m_mushroomhead_size;

			glNormal3f(
				this->Calculate_Normal(Fdata[0], Ldata[0]).x,
				this->Calculate_Normal(Fdata[0], Ldata[0]).y,
				this->Calculate_Normal(Fdata[0], Ldata[0]).z);

			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.5f, 1.f);
			glVertex3f(0, m_mushroomhead_size, 0);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glEnd();

			//오른쪽면
			Fdata[1].x = m_mushroomhead_size;
			Fdata[1].y = -2 * m_mushroomhead_size;
			Fdata[1].z = m_mushroomhead_size;

			Ldata[1].x = m_mushroomhead_size;
			Ldata[1].y = -2 * m_mushroomhead_size;
			Ldata[1].z = -m_mushroomhead_size;

			glNormal3f(
				this->Calculate_Normal(Fdata[1], Ldata[1]).x,
				this->Calculate_Normal(Fdata[1], Ldata[1]).y,
				this->Calculate_Normal(Fdata[1], Ldata[1]).z);

			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.5f, 1.f);
			glVertex3f(0, m_mushroomhead_size, 0);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glEnd();

			//뒷면
			Fdata[2].x = m_mushroomhead_size;
			Fdata[2].y = -2 * m_mushroomhead_size;
			Fdata[2].z = -m_mushroomhead_size;

			Ldata[2].x = -m_mushroomhead_size;
			Ldata[2].y = -2 * m_mushroomhead_size;
			Ldata[2].z = -m_mushroomhead_size;

			glNormal3f(
				this->Calculate_Normal(Fdata[2], Ldata[2]).x,
				this->Calculate_Normal(Fdata[2], Ldata[2]).y,
				this->Calculate_Normal(Fdata[2], Ldata[2]).z);

			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.5f, 1.f);
			glVertex3f(0, m_mushroomhead_size, 0);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glEnd();

			//왼쪽면
			Fdata[3].x = -m_mushroomhead_size;
			Fdata[3].y = -2 * m_mushroomhead_size;
			Fdata[3].z = -m_mushroomhead_size;

			Ldata[3].x = -m_mushroomhead_size;
			Ldata[3].y = -2 * MM_MOM_POSITIONCB;
			Ldata[3].z = m_mushroomhead_size;

			glNormal3f(
				this->Calculate_Normal(Fdata[3], Ldata[3]).x,
				this->Calculate_Normal(Fdata[3], Ldata[3]).y,
				this->Calculate_Normal(Fdata[3], Ldata[3]).z);

			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.5f, 1.f);
			glVertex3f(0, m_mushroomhead_size, 0);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glEnd();

			//아랫면
			Fdata[4].x = 0;
			Fdata[4].y = 0;
			Fdata[4].z = 2 * m_mushroomhead_size;

			Ldata[4].x = 2 * m_mushroomhead_size;
			Ldata[4].y = 0;
			Ldata[4].z = 0;

			glNormal3f(
				this->Calculate_Normal(Fdata[4], Ldata[4]).x,
				this->Calculate_Normal(Fdata[4], Ldata[4]).y,
				this->Calculate_Normal(Fdata[4], Ldata[4]).z);

			glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, m_mushroomhead_size);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(m_mushroomhead_size, -m_mushroomhead_size, -m_mushroomhead_size);
			glEnd();
		}
		glPopMatrix();

		//버섯 몸통 -> 구
		glPushMatrix();
		{
			glColor3f(0.8f, 0.8f, 0.8f);
			glTranslatef(0.0, m_mushroombody_rad / 2, 0.0);

			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			//------------------------------------------------------------구에대한 자동매핑
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glBindTexture(GL_TEXTURE_2D, m_textures[1]);

			//--------------------------------------------------------------

			glutSolidSphere(m_mushroombody_rad, 50, 50);

			//자동 매핑 해제
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		glPopMatrix();
	}
	glPopMatrix();
	//
	glDisable(GL_TEXTURE_2D);

}



CMonster::~CMonster()
{
}
