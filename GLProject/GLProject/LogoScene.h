#pragma once

#include "Scene.h"
#include "TextureLib.h"
class CLogoScene
{
public:
	CLogoScene();
	~CLogoScene();

	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);

	virtual void BuildScene(CGLFramework* pframework
		, int tag
	);

private:

	float m_fFadeIn = 0;
	Point2f			m_ptPos{ 100,100 };
	CTextureLibraray m_texLogo;

};

