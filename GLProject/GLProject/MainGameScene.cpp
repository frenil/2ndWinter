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
		if (player.x - (player_size.x*0.6) > object.x + object_size.x ||
			player.x + (player_size.x*0.6) < object.x - object_size.x ||
			player.z - (player_size.z*0.6) > object.z + object_size.z ||
			player.z + (player_size.z*0.6) < object.z - object_size.z)
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


		if ((player.x - (player_size.x*0.6) <= object.x + object_size.x&& player.x + (player_size.x*0.6) >= object.x - object_size.x)) {
			if ((player.z - (player_size.z*0.6) < object.z + object_size.z&&player.z + (player_size.z*0.6) > object.z - object_size.z)) {
				if ((player.y - (player_size.y - 10) < object.y + object_size.y&&player.y + (player_size.y - 10) > object.y - object_size.y)) {
					if (!temp.X)
						temp.X = true;
				}
			}
		}
		if ((player.z - (player_size.z*0.6) <= object.z + object_size.z&& player.z + (player_size.z*0.6) >= object.z - object_size.z)) {
			if ((player.x - (player_size.x*0.6) < object.x + object_size.z&&player.x + (player_size.x*0.6) > object.x - object_size.x)) {
				if ((player.y - (player_size.y - 10) < object.y + object_size.y&&player.y + (player_size.y - 10) > object.y - object_size.y)) {
					if (!temp.Z)
						temp.Z = true;
				}
			}
		}
	}
	else if (ViewType == 1) {
		if (player.x - (player_size.x*0.6) >= object.x + object_size.x ||
			player.x + (player_size.x*0.6) <= object.x - object_size.x)
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
		if ((player.x - (player_size.x*0.6) < object.x + object_size.x
			&& player.x + (player_size.x*0.6) >= object.x - object_size.x)) {
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
	auto end = chrono::system_clock::now();
	auto diff = end - Tstart;
	auto msec = chrono::duration_cast<chrono::milliseconds>(diff);
	beforeatime = msec.count();

	if(gametype==REPLAY)
		ReadSave();
	KeyConfirm();
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
		m_player.Update(beforeatime-deltatime);
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
				m_player.init();
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
	deltatime = beforeatime;
}
void CMainGameScene::Render()
{
	if (!isEnd) {
		if (ViewType == 0) {
			Mini(m_Camera.Getposition(), m_Camera.GetLookVector());
		}
		for (int i = 0; i < wall_count; i++) {
			if (ViewType != 0 || (m_wall[i].GetWallPos().x >= m_player.GetPosition().x - 90 && ViewType == 0))
				m_wall[i].DrawWall(m_Text.GetWallTexture());
		}
		for (int i = 0; i < mush_count; i++) {
			m_Mush[i].DrawMush();
		}
		for (int i = 0; i < block_count; i++) {
			m_Block[i].DrawBolck(m_Text.GetBlockTexture());
		}
		RenderDestinate();
		Sky();
		m_player.Render(ViewType);
	}
	else {
		glPushMatrix();
		{
			auto sz = m_pMasterFramework->GetWindowSize();
			CTextureLibraray::UsingTexture2D();
			{
				m_End.LoadTexture(0);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);  glVertex2f(0, 0);
					glTexCoord2f(0, 0);  glVertex2f(0, sz.y);
					glTexCoord2f(1, 0);  glVertex2f(sz.x, sz.y);
					glTexCoord2f(1, 1);  glVertex2f(sz.x, 0);
				}
				glEnd();
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
		SaveKey(SSPACE, PDOWN);
		isKeyDown[KEYSPACE] = true;
		break;
	case 'q':
		if (gametype == PLAY)
			m_saveKey.KeySave();
		m_pMasterFramework->BuildScene<CTitleScene>();
		glutMainLoop();

		break;
	case 'z':
	case 'Z':
		SaveKey(SZ, PDOWN);
		isKeyDown[KEYZ] = true;
		break;
	default:
		break;
	}
}

void CMainGameScene::SpecialKeyboard(int key, int x, int y)
{
		switch (key) {
		case GLUT_KEY_UP:
			if (!m_saveKey.isEqual(SUP, PDOWN))
				SaveKey(SUP, PDOWN);
			isMoveDown[MUP] = PDOWN;
			break;
		case GLUT_KEY_DOWN:
			if (!m_saveKey.isEqual(SDOWN,PDOWN))
				SaveKey(SDOWN, PDOWN);
			isMoveDown[MDOWN] = PDOWN;
			break;
		case GLUT_KEY_LEFT:
			if (!m_saveKey.isEqual(SLEFT, PDOWN))
				SaveKey(SLEFT, PDOWN);
			isMoveDown[MLEFT] = PDOWN;
			break;
		case GLUT_KEY_RIGHT:
			if (!m_saveKey.isEqual(SRIGHT, PDOWN))
				SaveKey(SRIGHT, PDOWN);
			isMoveDown[MRIGHT] = PDOWN;
			break;
		default:
			break;
		}
}

void CMainGameScene::SpecialKeyUp(int key, int x, int y)
{

		switch (key) {
		case GLUT_KEY_UP:
			isMoveDown[MUP] = PUP;
			if(!m_saveKey.isEqual(SUP,PUP))
				SaveKey(SUP, PUP);
			break;
		case GLUT_KEY_DOWN:
			isMoveDown[MDOWN] = PUP;
			if (!m_saveKey.isEqual(SDOWN, PUP))
				SaveKey(SDOWN, PUP);
			break;
		case GLUT_KEY_LEFT:
			isMoveDown[MLEFT] = PUP;
			if (!m_saveKey.isEqual(SLEFT, PUP))
				SaveKey(SLEFT, PUP);
			break;
		case GLUT_KEY_RIGHT:
			isMoveDown[MRIGHT] = PUP;
			if (!m_saveKey.isEqual(SRIGHT, PUP))
				SaveKey(SRIGHT, PUP);
			break;
		default:
			break;
		}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag, int state)
{
	CScene::BuildScene(pframework, tag,state);
	glClearColor(0.5, 0.5, 0.8, 1);
	SetStage();
	ChangeStage();
	m_Text.Loading();
	m_End.SetTexture(L"image/Clear.png");
	gametype = state;
	if (gametype == REPLAY) {
		m_saveKey.KeyLoad();
	}
	else
	{
		m_saveKey.Clear();
	}

	Tstart = chrono::system_clock::now();

}

void CMainGameScene::ReadSave()
{
	auto end = chrono::system_clock::now();
	auto diff = end - Tstart;
	auto msec = chrono::duration_cast<chrono::milliseconds>(diff);
	Key temp;
	float timesec = msec.count();
	while (!m_saveKey.isEnd()) {
		if (timesec < m_saveKey.GetTime())
			break;
		temp = m_saveKey.POPKey();
		if (temp.GetName() >= 0 && temp.GetName() <= 3) {
			isMoveDown[temp.GetName()] = temp.GetCondition();
		}
		else {
			isKeyDown[temp.GetName() - 4] = temp.GetCondition();
		}
	}
	if (m_saveKey.isEnd()) {
		for (int i = 0; i < 4; ++i) {
			isMoveDown[i] = INIT;
		}
	}
}

void CMainGameScene::Sky()
{
	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			glColor4f(1, 1, 1, 1);
			m_Text.GetSkyTexture().LoadTexture(0);
			glTranslatef(800, 500, 0);
			DrawQuad({ 0,0,-2900 }, 4000, true);

			glRotatef(90, 0, 1, 0);
			DrawQuad({ 0,0,4000 }, 20000, true);

			m_Text.GetSkyTexture().DisableTexture(0);
		}
		CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
}

void CMainGameScene::SaveKey(int name, int con)
{
	if (gametype == PLAY) {
		auto end = chrono::system_clock::now();
		auto diff = end - Tstart;
		auto msec = chrono::duration_cast<chrono::milliseconds>(diff);

		m_saveKey.UpdateKey(name, con, msec.count());
	}
}

void CMainGameScene::KeyConfirm()
{

	//키작용
	if (isKeyDown[KEYSPACE])
	{
		if (isEnd) {
			if (gametype == PLAY)
				m_saveKey.KeySave();
			m_pMasterFramework->BuildScene<CTitleScene>();
			glutMainLoop();
		}
		else {
			if (m_player.GetOnBlock()) {
				ViewType = (ViewType + 1) % 2;
				m_player.Move_X(0);
				m_player.Move_Z(0);
				m_Camera.SetView(ViewType, m_player.GetPosition());

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
		}
		SaveKey(SSPACE, INIT);
		isKeyDown[KEYSPACE] = false;
	}
	if (isKeyDown[KEYZ]) {
		m_player.Jump();
		m_player.SetJumpCount(1);
		SaveKey(SZ, INIT);
		isKeyDown[KEYZ] = false;

	}
	if (isMoveDown[MUP] == PDOWN) {
		if (ViewType == 0) {

			m_player.Move_X(1);
		}
	}
	else if (isMoveDown[MUP] == PUP) {
		if (ViewType == 0) {
			m_player.Move_X(0);
		SaveKey(SUP, INIT);
		isMoveDown[MUP] = INIT;
		}
	}
	if (isMoveDown[MDOWN] == PDOWN) {
		if (ViewType == 0) {
			m_player.Move_X(-1);
		}
	}
	else if (isMoveDown[MDOWN] == PUP) {
		if (ViewType == 0) {
			m_player.Move_X(0);
		SaveKey(SDOWN, INIT);
		isMoveDown[MDOWN] = INIT;
		}
	}
	if (isMoveDown[MLEFT] == PDOWN) {
		if (ViewType == 0) {
			m_player.Move_Z(-1);
		}
		else if (ViewType == 1) {
			m_player.Move_X(-1);
		}
	}
	else if (isMoveDown[MLEFT] == PUP) {
		if (ViewType == 0) {
			m_player.Move_Z(0);
		}
		else if (ViewType == 1) {
			m_player.Move_X(0);
		}
		isMoveDown[MLEFT] = INIT;
		SaveKey(SLEFT, INIT);
	}
	if (isMoveDown[MRIGHT] == PDOWN) {
		if (ViewType == 0) {
			m_player.Move_Z(1);
		}
		else if (ViewType == 1) {
			m_player.Move_X(1);
		}
	}
	else if (isMoveDown[MRIGHT] == PUP) {
		if (ViewType == 0) {
			m_player.Move_Z(0);
		}
		else if (ViewType == 1) {
			m_player.Move_X(0);
		}
		isMoveDown[MRIGHT] = INIT;
		SaveKey(SRIGHT, INIT);
	}
}

void CMainGameScene::ChangeStage()
{
	mush_count = wall_count = block_count = 0;
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

void CMainGameScene::Mini(Vec3f player, Vec3f pvec)
{
	glPushMatrix(); {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		{
			glTranslatef(player.x + (pvec.x * 100), player.y + (pvec.y * 99), player.z + 50 + (pvec.z * 99));
			glRotatef(90, 0, 1, 0);
			glRotatef(30, 1, 0, 0);
			glTranslatef(0, 50, -10);
			glRectf(-30, -30, 20, 30);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(player.x - 5 + (pvec.x * 100), player.y + (pvec.y * 99), player.z + 50 + (pvec.z * 99));
			glScalef(0.3, 0.3, 0.3);
			glRotatef(90, 0, 1, 0);
			glRotatef(30, 1, 0, 0);
			glPushMatrix();
			{
				glTranslatef(-m_player.GetPosition().z / 10,
					50 + (m_player.GetPosition().x / 10), 0);
				glColor3f(1, 0, 0);
				glTranslatef(0, 50, -51);
				DrawCircle(0, 0, 5, 12);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-m_stage[stage_number].GetDestinate().z / 10,
					50 + (m_stage[stage_number].GetDestinate().x / 10), 0);
				glColor3f(1, 1, 0);
				DrawQuad({ 0,50,-51 }, 7, true);
			}
			glPopMatrix();
			for (int i = 0; i < wall_count; i++) {
				glPushMatrix();
				{
					glTranslatef(-m_wall[i].GetWallPos().z / 10,
						50 + (m_wall[i].GetWallPos().x / 10), 0);
					glColor3f(0, 0, 0);
					DrawQuad({ 0,50,-50 }, 10, true);
				}
				glPopMatrix();
			}
			for (int i = 0; i < block_count; i++) {
				glPushMatrix();
				{
					glTranslatef(-m_Block[i].GetBlockPos().z / 10,
						50 + (m_Block[i].GetBlockPos().x / 10), 0);
					glColor3f(0.7, 0.54, 0.15);
					DrawQuad({ 0,50,-50 }, 10, true);

				}
				glPopMatrix();
			}

		}
		glPopMatrix();
		glDisable(GL_BLEND);
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