#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "TitleScene.h"


CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Update()
{
	m_fFadeIn += 0.016;
	if (m_fFadeIn > 1.5f&&state!=2) {
		state = 1;
	}
	if (m_fFadeIn >= 10) {
		state = 0;
		m_fFadeIn = 0;
	}
}

void CTitleScene::Render()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	CTextureLibraray::UsingTexture2D();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1, 1, 1, min(m_fFadeIn,1.f));
		if (state == 0) {
			m_texLogo.LoadTexture(0);
		}
		else if (state == 1) {
			m_Title.LoadTexture(0);
		}
		else if (state == 2) {
			m_Help.LoadTexture(0);
		}
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

void CTitleScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, sz.x, sz.y, 0, -500, 500);
	glMatrixMode(GL_MODELVIEW);

}

void CTitleScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_pMasterFramework->BuildScene<CMainGameScene>();
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CTitleScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.f,0.f,0.f, 1);
	Reshape();
	m_texLogo.SetTexture(L"image/warp_small.png");
	m_Title.SetTexture(L"image/title.png");
	m_Help.SetTexture(L"image/help.png");
}

void CTitleScene::Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
		if (state >= 1) {
			m_pMasterFramework->BuildScene<CMainGameScene>();
		}
	case 'i':
	case 'I':
		state = 2;
	default:
		break;
	}
}
