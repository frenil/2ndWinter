#pragma once

#include <gl/glut.h>
#include "GetTexture.h"
#include "GlobalDefine.h"
#include "Vector3D.h"
#include <Windows.h>

class CMonster
{
private:
	int m_texture_size = 512;
	int m_texture_num = 2;
	float m_mushroomhead_size = 100;
	float m_mushroombody_rad = 100;

	GLubyte * m_TexBits;
	GLuint m_textures[2];
	BITMAPINFO * m_info;

	//³ë¸»
	CKH_NORM_DATA Fdata[5];
	CKH_NORM_DATA Ldata[5];

	Vec3f ckh_vec3d{ 0.f,0.f,0.f };
	Vec3f ckh_other_vec3d{ 0.f,0.f,0.f };
	//
	CGetTexture *monster_getLoad;
	bool show_once = true;

	float scale_for_x = 1.0;
	float scale_for_y = 1.0;
	bool Limit_scale_x = false;
	bool Limit_scale_y = false;
protected:


public:
	CMonster();
	void UpdateMush_FUNC();
	void MakeMushroomTexture_FUNC();
	void DrawMushroom_FUNC();
	Vec3D<float> Calculate_Normal(CKH_NORM_DATA fdata, CKH_NORM_DATA ldata);
	~CMonster();
};

