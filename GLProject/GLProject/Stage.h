#pragma once
#include "stdafx.h"
#include "Vector3D.h"
class CStage
{
	Vec3f Block[1000];
	int Block_Count{0};
	Vec3f Wall[100];
	int Wall_Count{ 0 };
	Vec3f Mush[100];
	int Mush_Count{ 0 };
	Vec3f Start;
	Vec3f Destinate;
	Vec3f DSize {30,30,30};

public:
	CStage();
	~CStage();
	void SetBlock(Vec3f sample, int n) { Block[n] = sample; }
	void SetWall(Vec3f sample, int n) { Wall[n] = sample; }
	void SetMush(Vec3f sample, int n) { Mush[n] = sample; }
	void SetStart(Vec3f sample) { Start = sample; }
	void SetDestinate(Vec3f sample) { Destinate = 100*sample; }
	
	void SetBlockCount(int n) { Block_Count+= n; }
	void SetWallCount(int n)  { Wall_Count += n; }
	void SetMushCount(int n)  { Mush_Count += n; }
	
	int GetBlockCount() {return Block_Count; }
	int GetWallCount( ) {return Wall_Count ; }
	int GetMushCount( ) {return Mush_Count ; }
	
	void DrawDestinate();

	Vec3f GetBlock(int n) { return Block[n]; }
	Vec3f GetWall(int n) { return Wall[n]; }
	Vec3f GetMush(int n) { return Mush[n]; }
	Vec3f GetStart() { return Start; }
	Vec3f GetDestinate() { return Destinate; }
	Vec3f GetSize() { return DSize; }
};

