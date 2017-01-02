#pragma once
#include "Light.h"
#include "Scene.h"
#include "Camera.h"
#include "TextureLib.h"
#include "block.h"
#include "Player.h"
#include "Wall.h"
#include "Mush.h"
#include "Stage.h"
#include "Drender.h"
#include "TextureLoad.h"

class CMainGameScene :
	public CScene
{
public:
	CMainGameScene();
	virtual ~CMainGameScene();	
public:
	COLLIDETYPE Collide(Vec3f player, Vec3f player_size, Vec3f object, Vec3f object_size);
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void SpecialKeyboard(int key, int x, int y);
	virtual void SpecialKeyUp(int key ,int x, int y);

	virtual void BuildScene(	  CGLFramework* pframework
								, int tag
	);

	void ChangeStage();
	void RenderDestinate();
	COLLIDETYPE ResetCollide() {return COLLIDETYPE{ false,false, false, false }; }
	void SetStage();
private:
	CSpotLight		m_light;
	CExitCube		drender;
	CPlayer			m_player;
	CCamera			m_Camera;
	CStage			m_stage[10];
	CMush			m_Mush[100];
	CWall			m_wall[100];
	CBlock			m_Block[1000];
	Point2f			m_ptPos			{100,100}	;
	CTextureLibraray m_texLib;
	CTextureLoad m_Text;
	CTextureLibraray m_texLogo;
	CTextureLibraray m_End;
	bool isEnd = false;
	bool isClear = false;
	int block_count = 0;
	int wall_count = 0;
	int mush_count = 0;
	int ViewType=1;
	int stage_number = 0;
	int total_stage=0;
	COLLIDETYPE Ctype;
	COLLIDETYPE Wtype;
	COLLIDETYPE Mtype;
};

