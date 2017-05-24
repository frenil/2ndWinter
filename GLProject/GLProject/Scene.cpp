#include "stdafx.h"
#include "GLFramework.h"
#include "Scene.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
}


void CScene::Render()
{
}

void CScene::Reshape()
{
}

void CScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CScene::Keyboard(unsigned char key, int x, int y)
{
}

void CScene::SpecialKeyboard(int key, int x, int y)
{
}

void CScene::SpecialKeyUp(int key, int x, int y)
{
}

void CScene::BuildScene(CGLFramework * pframework, int tag, int state)
{
	m_pMasterFramework = pframework;
	State = state;
	m_iTag = tag;
}
