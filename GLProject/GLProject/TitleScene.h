#pragma once
#include "Scene.h"
#include "Player.h"
#include "TextureLib.h"

class CTitleScene :
	public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();

public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void BuildScene(CGLFramework* pframework
		, int tag
	);

private:
	int state = 0;
	float m_fFadeIn = 0;
	Point2f			m_ptPos{ 100,100 };
	CTextureLibraray m_texLogo;
	CTextureLibraray m_Title;
	CTextureLibraray m_Help;

};

