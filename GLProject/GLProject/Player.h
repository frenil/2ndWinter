#pragma once
#include "stdafx.h"
#include "Character.h"
class CPlayer
{
	Character render;
	Vec3f preposition;
	Vec3f position	;
	Vec3f SavePos	;
	Vec3f movevec	{	0,   0,   0	};
	Vec3f size ;
	bool onBlock	{ true };
	bool isDie		{ false };
	float Yspeed	{ 0 };
	float Speed	;
	int player_state;
	int die_count	{ 0 };
	int jump_count	{ 0 };
public:
	CPlayer();
	~CPlayer();
	void Update();
	void SetSpeed(int x){ Yspeed = x; }
	void Jump();
	void Move_X(int x) { movevec.x = x; }
	void Move_Y(int y) { movevec.y = y; }
	void Move_Z(int z) { movevec.z = z; }
	void MoveBackX() {
		position.x = preposition.x;
	}
	void MoveBackZ() {
		position.z = preposition.z;
	}
	void isOnBlock(bool a) { onBlock = a; }
	bool GetOnBlock() { return onBlock; }
	void SetPosition(Vec3f pos) {Speed =3; size.x = 90; size.y = 100; size.z = 90; preposition = position = pos; }
	void SetYPos(float pos) { position.y = pos; }
	void SetZPos(float pos) { position.z = pos; }
	
	void SetJumpCount(int n) { jump_count = n; }
	bool GetDie() { return isDie; }
	void Die() { isDie = true; }
	void SetSave(Vec3f input) { SavePos = input; }
	Vec3f GetSize() { return size; }
	Vec3f GetPosition() {  return position; }
	Vec3f GetVector() { return movevec; }
	void RenderDie();
	void Render(int view);
};

