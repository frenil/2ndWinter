#pragma once
#include "stdafx.h"
#include "Vector3D.h"
#include "GlobalDefine.h"
#include "Character.h"
#include "GetTexture.h"
#include <gl/glut.h>
#include <Windows.h>

class CSpotLight
{
private:
	
	GLubyte * m_TexBits;
	GLuint m_textures[1];
	BITMAPINFO * m_info;

	int m_texture_size = 512;
	int m_texture_num = 1;

	CGetTexture *spot_getload;
	bool show_once = true;

public:
	CSpotLight();
	void Light(Vec3f player, bool isOn);
	~CSpotLight();
};

