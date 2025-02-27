#pragma once

class CGLFramework;



class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void SpecialKeyboard(int key, int x, int y);
	virtual void SpecialKeyUp(int key, int x, int y);
	virtual void BuildScene(	  CGLFramework* pframework
								, int tag
		, int state
	);

	bool MatchTag(const int tag) const { return { tag == m_iTag }; }

protected:


	CGLFramework*	m_pMasterFramework;
	int				m_iTag;	
	int				State;
};

