#pragma once
#include "stdafx.h"
#include "Vector3D.h"
#include "Mrender.h"

class CMush
{
private:
	CMonster render;
	bool isDie{ false };
	Vec3f position;
	Vec3f vertex;
	Vec3f size{ 100,90,100 };
	bool collide{ false }; 
public:
	CMush();
	~CMush();
	void Update();
	void isCollide() { collide = true; };
	void SetMushPos(Vec3f a);

	bool GetDie() { return isDie; }

	Vec3f GetMushPos() { return vertex; }
	Vec3f GetSize() { return size; }
	void DrawMush();
	void Live() { isDie = false; }
	void Die() { isDie = true; }
};

