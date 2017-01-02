#include "stdafx.h"
#include "block.h"
#include "TextureLoad.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::SetBlockPos(Vec3f input)
{
	
	vertex = 100 * input;
}


void CBlock::DrawBolck(CTextureLibraray m_Block)
{
	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			glColor4f(1, 1, 1, 1);
			m_Block.LoadTexture(0);

			glTranslatef(vertex.x, vertex.y, vertex.z);
			DrawQuad({ 0,0,-50 }, 100, true);
			DrawQuad({ 0,0,50 }, 100, true);
			
			glPushMatrix();
			{
				glRotatef(90, 0, 1, 0);
				DrawQuad({ 0,0,-50 }, 100, true);
				DrawQuad({ 0,0,50 },  100, true);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(90, 1, 0, 0);
				DrawQuad({ 0,0,-50 }, 100, true);
				DrawQuad({ 0,0,50 },  100, true);
			}
			glPopMatrix();
			m_Wall.DisableTexture(0);
		}
		CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
}

