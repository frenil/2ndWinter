#pragma once
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
#include "SaveKey.h"

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
	void ReadSave();
	void Sky();
	void SaveKey(int,int);
	void KeyConfirm();
	void ChangeStage();
	void RenderDestinate();
	void Mini(Vec3f player, Vec3f pvec);
	COLLIDETYPE ResetCollide() {return COLLIDETYPE{ false,false, false, false }; }
	void SetStage();
private:

	std::chrono::time_point<std::chrono::system_clock> Tstart ;
	int				gametype;
	list<Key>		replay;
	CSaveKey		m_saveKey;
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
	
	bool isKeyDown[2]{ false,false };
	int isMoveDown[4]{ INIT,INIT,INIT,INIT };

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

