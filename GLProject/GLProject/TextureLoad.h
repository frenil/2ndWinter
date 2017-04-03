#pragma once
#include "TextureLib.h"

class CTextureLoad
{
private:
	CTextureLibraray m_Block;
	CTextureLibraray m_Wall;
	CTextureLibraray m_Sky;

public:
	CTextureLoad();
	~CTextureLoad();
	void Loading();


	CTextureLibraray GetWallTexture() { return m_Wall; }
	CTextureLibraray GetBlockTexture() { return m_Block; }
	CTextureLibraray GetSkyTexture() { return m_Sky; }
};

