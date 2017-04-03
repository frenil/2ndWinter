#include "stdafx.h"
#include "TextureLoad.h"



CTextureLoad::CTextureLoad()
{
}


CTextureLoad::~CTextureLoad()
{
}

void CTextureLoad::Loading()
{
	m_Wall.SetTexture(L"image/steal.png");
	m_Block.SetTexture(L"image/wall.png");
	m_Sky.SetTexture(L"image/sky.png");

}
