#pragma once
#include "stdafx.h"
#include "Vector3D.h"
#include "TextureLib.h"
class CWall
{
private:
	Vec3f position;
	Vec3f vertex;
	Vec3f size		{ 100,500,100 };
	bool collide	{false};
public:
	CWall();
	~CWall();
	void Update();
	void isCollide() { collide = true; };
	void SetWallPos(Vec3f a);
	Vec3f GetWallPos() { return vertex; }
	Vec3f GetSize() { return size; }
	void DrawWall(CTextureLibraray m_Wall);
};


