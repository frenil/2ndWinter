#pragma once
#include "stdafx.h"
#include "Vector3D.h"
#include "TextureLib.h"
#include "Brender.h"
class CBlock
{
private :
	CBrender render;
	Vec3f vertex;
	Vec3f size		{100,100,100};
public:
	CBlock();
	~CBlock();
	void SetBlockPos(Vec3f input);
	Vec3f GetBlockPos() { return vertex; }
	Vec3f GetSize() { return size; }
	void DrawBolck();
};

