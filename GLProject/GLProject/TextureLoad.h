#pragma once
#include "TextureLib.h"

class CTextureLoad
{
private:
	CTextureLibraray m_Block;
	CTextureLibraray m_Wall;

public:
	CTextureLoad();
	~CTextureLoad();
	void Loading();


	CTextureLibraray GetWallTexture() { return m_Wall; }
	CTextureLibraray GetBlockTexture() { return m_Block; }
};

