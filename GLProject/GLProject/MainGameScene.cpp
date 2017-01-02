#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "Camera.h"
#include "TitleScene.h"
#include "TextureLib.h"

CMainGameScene::CMainGameScene()
{
}


CMainGameScene::~CMainGameScene()
{
}

COLLIDETYPE CMainGameScene::Collide(Vec3f player, Vec3f player_size, Vec3f object, Vec3f object_size)
{
	COLLIDETYPE temp = Ctype;
	object_size *= 0.5;
	player_size *= 0.5;
	if (ViewType == 0) {
		if (player.x - player_size.x > object.x + object_size.x ||
			player.x + player_size.x < object.x - object_size.x ||
			player.z - player_size.z > object.z + object_size.z ||
			player.z + player_size.z < object.z - object_size.z)
		{
		}
		else {
			if (player.y + player_size.y > object.y - object_size.y&&player.y - player_size.y < object.y - object_size.y) {
				if (!temp.DOWN)temp.DOWN = true;
			}
			if (player.y - player_size.y < object.y + object_size.y&&player.y + player_size.y > object.y + object_size.y) {
				if (!temp.UP)temp.UP = true;
			}
		}


		if ((player.x - player_size.x <= object.x + object_size.x&& player.x + player_size.x >= object.x - object_size.x)) {
			if ((player.z - player_size.z < object.z + object_size.z&&player.z + player_size.z > object.z - object_size.z)) {
				if ((player.y - (player_size.y - 10) < object.y + object_size.y&&player.y + (player_size.y - 10) > object.y - object_size.y)) {
					if (!temp.X)
						temp.X = true;
				}
			}
		}
		if ((player.z - player_size.z <= object.z + object_size.z&& player.z + player_size.z >= object.z - object_size.z)) {
			if ((player.x - player_size.x < object.x + object_size.z&&player.x + player_size.x > object.x - object_size.x)) {
				if ((player.y - (player_size.y - 10) < object.y + object_size.y&&player.y + (player_size.y - 10) > object.y - object_size.y)) {
					if (!temp.Z)
						temp.Z = true;
				}
			}
		}
	}
	else if (ViewType == 1) {
			if (player.x - player_size.x >= object.x + object_size.x ||
				player.x + player_size.x <= object.x - object_size.x)
			{
			}
			else {
				if (player.y + player_size.y > object.y - object_size.y
					&&player.y - player_size.y < object.y - object_size.y) {
					if (!temp.DOWN)
						temp.DOWN = true;
				}
				if (player.y - player_size.y < object.y + object_size.y
					&&player.y + player_size.y > object.y + object_size.y) {
					if (!temp.UP)
						temp.UP = true;
				}
			}
			if ((player.x - player_size.x < object.x + object_size.x
				&& player.x + player_size.x >= object.x - object_size.x)) {
				if ((player.y - (player_size.y - 10) < object.y + object_size.y
					&&player.y + (player_size.y - 10) > object.y - object_size.y)) {
					if (!temp.X)
						temp.X = true;
				}
			}
		}
	return temp;
}

void CMainGameScene::Update()
{
	if (!isEnd) {
		Ctype = ResetCollide();
		m_player.isOnBlock(false);
		for (int i = 0; i < block_count; i++) {
			Ctype = Collide(m_player.GetPosition(), m_player.GetSize(), m_Block[i].GetBlockPos(), m_Block[i].GetSize());
			if (Ctype.DOWN) {
				m_player.SetSpeed(-1);
				Ctype.DOWN = false;
			}
			if (Ctype.UP) {
				m_player.SetYPos(49 + m_Block[i].GetBlockPos().y + (m_Block[i].GetSize().y * 0.5f));
				m_player.isOnBlock(true);
				m_player.SetJumpCount(0);
				Ctype.UP = false;
			}
			if (Ctype.X)
			{
				m_player.MoveBackX();
				m_player.Move_X(0);
				Ctype.X = false;
			}
			if (Ctype.Z)
			{
				m_player.MoveBackZ();
				m_player.Move_Z(0);
				Ctype.Z = false;
			}
		}
		Ctype = ResetCollide();
		//벽돌+주인공 충돌
		for (int i = 0; i < wall_count; i++) {
			Ctype = Collide(m_player.GetPosition(), m_player.GetSize(), m_wall[i].GetWallPos(), m_wall[i].GetSize());
			if (Ctype.DOWN) {
				m_player.Die();
				Ctype.DOWN = false;
			}
			if (Ctype.X)
			{
				m_player.MoveBackX();
				m_player.Move_X(0);
				Ctype.X = false;
			}
			if (Ctype.Z)
			{
				m_player.MoveBackZ();
				m_player.Move_Z(0);
				Ctype.Z = false;
			}
		}
		Ctype = ResetCollide();
		//벽+주인공충돌
		for (int j = 0; j < block_count; j++) {
			for (int i = 0; i < wall_count; i++) {
				Ctype = Collide(m_Block[j].GetBlockPos(), m_Block[j].GetSize(), m_wall[i].GetWallPos(), m_wall[i].GetSize());
				if (Ctype.DOWN) {
					m_wall[i].isCollide();
					Ctype.DOWN = false;
					break;
				}
			}
		}
		//벽+벽돌 충돌
		for (int i = 0; i < mush_count; i++) {
			if (m_Mush[i].GetDie())continue;
			Ctype = ResetCollide();
			Ctype = Collide(m_player.GetPosition(), m_player.GetSize(), m_Mush[i].GetMushPos(), m_Mush[i].GetSize());
			if (Ctype.UP) {
				m_Mush[i].Die();
				m_player.SetJumpCount(0);
				m_player.Jump();
				m_player.SetJumpCount(0);
				Ctype.DOWN = false;
				break;
			}
			if (Ctype.X)
			{
				m_player.Die();
				Ctype.X = false;
			}
			if (Ctype.Z)
			{
				m_player.Die();
				Ctype.Z = false;
			}
		}
		//버섯+주인공 충돌
		for (int i = 0; i < wall_count; i++) {
			m_wall[i].Update();
		}
		for (int i = 0; i < mush_count; i++) {
			m_Mush[i].Update();
		}
		drender.Update_Exitcube();
		if (m_player.GetDie())
		{
			for (int i = 0; i < mush_count; i++) {
				m_Mush[i].Live();
			}
		}
		m_player.Update();
		m_Camera.SetView(ViewType, m_player.GetPosition());

		Ctype = ResetCollide();
		Ctype = Collide(m_player.GetPosition(), m_player.GetSize(),
			m_stage[stage_number].GetDestinate(), m_stage[stage_number].GetSize());
		if (Ctype.DOWN == true || Ctype.UP == true || Ctype.X == true || Ctype.Z == true) {
			isClear = true;
		}
		if (isClear) {
			stage_number++;
			if (stage_number == total_stage) {
				isEnd = true;
			}
			else {
				ChangeStage();
				isClear = false;
			}
		}
		m_ptPos.x += 10.f;
		if (m_ptPos.x > m_pMasterFramework->GetWindowSize().x)
			m_ptPos.x -= m_pMasterFramework->GetWindowSize().x;
	}
	else {
		auto sz = m_pMasterFramework->GetWindowSize();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, sz.x, sz.y, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
	}
}

void CMainGameScene::Render()
{
	if (!isEnd) {
		
		for (int i = 0; i < wall_count; i++) {
			m_wall[i].DrawWall(m_Text.GetWallTexture());
		}
		for (int i = 0; i < mush_count; i++) {
			m_Mush[i].DrawMush();
		}
		for (int i = 0; i < block_count; i++) {
			m_Block[i].DrawBolck(m_Text.GetBlockTexture());
		}
		RenderDestinate();
		m_player.Render(ViewType);
	}
	else {
		glPushMatrix();
		{
			auto sz = m_pMasterFramework->GetWindowSize();
			CTextureLibraray::UsingTexture2D();
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				m_End.LoadTexture(0);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);  glVertex2f(0, 0);
					glTexCoord2f(0, 0);  glVertex2f(0, sz.y);
					glTexCoord2f(1, 0);  glVertex2f(sz.x, sz.y);
					glTexCoord2f(1, 1);  glVertex2f(sz.x, 0);
				}
				glEnd();
				glDisable(GL_BLEND);
			}
			CTextureLibraray::StopUsingTexture2D();

		}
		glPopMatrix();
	}
}

void CMainGameScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	if (ViewType == 0) {
		m_Camera.SetAspect(static_cast<float> (sz.x) / static_cast<float>(sz.y));
		m_Camera.LookAt();
	}
	else if (ViewType == 1) {
		glOrtho(-1000, 1000, -1000, 1000, -500, 500);
	}
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_Camera.Move({ 0,0,-1 });
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		m_Camera.Move({ 0,0,1 });
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CMainGameScene::Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
		if (isEnd) {
			m_pMasterFramework->BuildScene<CTitleScene>();
			glutMainLoop();
		}
		else {
			if (m_player.GetOnBlock()) {
				ViewType = (ViewType + 1) % 2;
				m_player.Move_X(0);
				m_player.Move_Z(0);
				m_Camera.SetView(ViewType, m_player.GetPosition());
			}
			if (ViewType == 0)
			{
				float tempZ = -1000;
				for (int i = 0; i < block_count; i++) {
					if (((int)m_player.GetPosition().x + 50) / 100 == ((int)m_Block[i].GetBlockPos().x + 50) / 100
						&& ((int)m_player.GetPosition().y) / 100 == ((int)m_Block[i].GetBlockPos().y) / 100) {
						if (tempZ <= m_Block[i].GetBlockPos().z) {
							tempZ = m_Block[i].GetBlockPos().z;
						}
					}
				}
				m_player.SetZPos(tempZ);

			}
		}
		break;
	case 'q':
		isEnd = true;

		break;
	case 'z':
	case 'Z':
		m_player.Jump();
		m_player.SetJumpCount(1);
		break;
	default:
		break;
	}
}

void CMainGameScene::SpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (ViewType == 0) {
			m_player.Move_X(1);
		}
		break;
	case GLUT_KEY_DOWN:
		if (ViewType == 0) {
			m_player.Move_X(-1);
		}
		break;
	case GLUT_KEY_LEFT:
		if (ViewType == 0) {
			m_player.Move_Z(-1);
		}
		else if (ViewType == 1) {
			m_player.Move_X(-1);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (ViewType == 0) {
			m_player.Move_Z(1);
		}
		else if (ViewType == 1) {
			m_player.Move_X(1);
		}
		break;
	default:
		break;
	}
}

void CMainGameScene::SpecialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		if (ViewType == 0) {
			m_player.Move_X(0);
		}
		break;
	case GLUT_KEY_LEFT:
		if (ViewType == 0) {
			m_player.Move_Z(0);
		}
		else if (ViewType == 1) {
			m_player.Move_X(0);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (ViewType == 0) {
			m_player.Move_Z(0);
		}
		else if (ViewType == 1) {
			m_player.Move_X(0);
		}
		break;
	default:
		break;
	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);
	SetStage();
	ChangeStage();
	m_Text.Loading();
	m_End.SetTexture(L"image/Clear.png");

}

void CMainGameScene::ChangeStage()
{
	mush_count=wall_count=block_count = 0;
	ViewType = 1;
	m_player.SetPosition(m_stage[stage_number].GetStart());
	m_player.SetSave(m_stage[stage_number].GetStart());
	m_Camera.SetView(ViewType, m_player.GetPosition());

	for (int i = 0; i < m_stage[stage_number].GetBlockCount(); i++) {
		m_Block[block_count++].SetBlockPos(m_stage[stage_number].GetBlock(i));
	}
	for (int i = 0; i < m_stage[stage_number].GetWallCount(); i++) {
		m_wall[wall_count++].SetWallPos(m_stage[stage_number].GetWall(i));
	}
	for (int i = 0; i < m_stage[stage_number].GetMushCount(); i++) {
		m_Mush[mush_count].SetMushPos(m_stage[stage_number].GetMush(i));
		m_Mush[mush_count++].Live();
	}
}

void CMainGameScene::RenderDestinate()
{
	glPushMatrix();
	{
		Vec3f pos = m_stage[stage_number].GetDestinate();
		Vec3f Dsize = m_stage[stage_number].GetSize();
		glColor3f(0, 1, 0);
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(Dsize.x / 200, Dsize.y / 200, Dsize.z / 200);
		drender.Draw_Exitcube();
	}
	glPopMatrix();
}


void CMainGameScene::SetStage()
{
	
	ifstream ifs("stage_set.txt");
	
	int Stage_count;
	int b_count;
	int x, y, z;
	ifs >> Stage_count;
	total_stage = Stage_count;
	for (int i = 0; i < Stage_count; i++) {
		ifs >> b_count;
		m_stage[i].SetBlockCount(b_count);
		for (int j = 0; j < b_count; j++) {
			ifs >> x; ifs >> y;	ifs >> z;
			m_stage[i].SetBlock(Vec3f{ x,y,z }, j);
		}
		ifs >> b_count;
		m_stage[i].SetWallCount(b_count);
		for (int j = 0; j < b_count; j++) {
			ifs >> x; ifs >> y;	ifs >> z;
			m_stage[i].SetWall(Vec3f{ x,y,z }, j);
		}

		ifs >> b_count;
		m_stage[i].SetMushCount(b_count);
		for (int j = 0; j < b_count; j++) {
			ifs >> x; ifs >> y;	ifs >> z;
			m_stage[i].SetMush(Vec3f{ x,y,z }, j);
		}
		ifs >> x; ifs >> y;	ifs >> z;
		m_stage[i].SetStart(Vec3f{ x,y,z });
		ifs >> x; ifs >> y;	ifs >> z;
		m_stage[i].SetDestinate(Vec3f{ x,y,z });
	}
	ifs.close();
}
/*
스테이지수
블록 개수
블록 위치
벽 개수
벽위치
버섯개수
버섯위치
시작
끝

반복

*/