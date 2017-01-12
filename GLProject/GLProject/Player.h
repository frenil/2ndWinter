#pragma once
#include "stdafx.h"
class CPlayer
{
	Vec3f preposition;
	Vec3f position	;
	Vec3f SavePos	;
	Vec3f movevec	{	0,   0,   0	};
	Vec3f size ;
	bool onBlock	{ true };
	bool isDie		{ false };
	float Yspeed	{ 0 };
	float Speed	;
	int die_count	{ 0 };
	int jump_count	{ 0 };
public:
	CPlayer();
	~CPlayer();
	void Update();
	void SetSpeed(int x){ Yspeed = x; }
	void Jump();
	void Move_X(int x) {
		if (movevec.x != 0 && x == 0)
			movevec.x = 0;
		else if (movevec.x < x) {
			movevec.x += 0.2;
			if (movevec.x >= x)
				movevec.x = x;
		}
		else if (movevec.x > x) {
			movevec.x -= 0.2;
			if (movevec.x <= x)
				movevec.x = x;
		}
		movevec = Nomalize(movevec);

	}
	void Move_Z(int z) {
		if (movevec.z != 0 && z == 0)
			movevec.z = 0;
		else if (movevec.z < z) {
			movevec.z += 0.2;
			if (movevec.z >= z)
				movevec.z = z;
		}
		else if (movevec.z > z) {
			movevec.z -= 0.2;
			if (movevec.z <= z)
				movevec.z = z;
		}
	//	movevec = Nomalize(movevec);
	}
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

