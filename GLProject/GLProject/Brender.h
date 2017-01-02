#pragma once
#include "stdafx.h"
#include "GlobalDefine.h"
#include "GetTexture.h"
#include "Vector3D.h"

class CBrender
{
private:
	//텍스쳐
	int m_texture_size = 512;
	int m_texture_num = 1;
	float m_brick_size = 0.5;

	GLubyte * m_TexBits;
	GLuint m_textures[1];
	BITMAPINFO * m_info;

	//노말
	CKH_NORM_DATA Fdata[6];
	CKH_NORM_DATA Ldata[6];

	Vec3f ckh_vec3d{ 0.f,0.f,0.f };
	Vec3f ckh_other_vec3d{ 0.f,0.f,0.f };
	//

	CGetTexture *get_load;
	bool show_once = true;
protected:

public:
	CBrender();
	void MakeBrickTexture_FUNC();
	void MakeNORMAL_FUNC();
	void DrawBrick_FUNC();
	Vec3D<float> Calculate_Normal(CKH_NORM_DATA fdata, CKH_NORM_DATA ldata);
	~CBrender();

};



