#pragma once
#include "stdafx.h"
class CPlayer
{
	Vec3f preposition;
	Vec3f position	;
	Vec3f SavePos	;
	Vec3f movevec	{	0,   0,   0	};
	Vec3f size ;
	GLfloat Mat[16];
	bool onBlock	{ true };
	bool isDie		{ false };
	float Yspeed	{ 0 };
	float Speed	;
	int angle_annie	{ 0 };
	int angle_speed	{ 2 };
	int rotate_rad;
	int die_count	{ 0 };
	int jump_count	{ 0 };
public:
	CPlayer();
	~CPlayer();
	void Update(float deltatime);
	void SetSpeed(int x){ Yspeed = x; }
	void Jump();
	void init();
	void Move_X(int x) {
		movevec.x = x;
	}
	void Move_Z(int z) {
		movevec.z = z;
	}
	void MoveBackX() {
		position.x = preposition.x;
	}
	void MoveBackZ() {
		position.z = preposition.z;
	}
	void isOnBlock(bool a) { onBlock = a; angle_speed = 10; }
	bool GetOnBlock() { return onBlock; }
	void SetPosition(Vec3f pos) {Speed =3; size.x = 90; size.y = 100; size.z = 90; preposition = position = pos; }
	void SetYPos(float pos) { position.y = pos; }
	void SetZPos(float pos) { position.z = pos; }
	
	void SetJumpCount(int n) { jump_count = n; angle_speed = 2;	}
	bool GetDie() { return isDie; }
	void Die() { isDie = true; }
	void SetSave(Vec3f input) { SavePos = input; }
	Vec3f GetSize() { return size; }
	Vec3f GetPosition() {  return position; }
	Vec3f GetVector() { return movevec; }
	void RenderDie();
	void Render(int view);
};

