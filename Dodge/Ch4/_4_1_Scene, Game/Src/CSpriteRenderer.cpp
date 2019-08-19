#include "DXUT.h"
#include "CSpriteRenderer.h"

void CSpriteRenderer::Create(const WCHAR* filename)
{
	if (FAILED(D3DXCreateSprite(DXUTGetD3D9Device(), &m_Sprite)))
	{
		MessageBox(DXUTGetHWND(), L"Err: Sprite Create", L"Err", MB_OK);
		return;
	}

	m_pTexture = g_Game.m_ResourceManager.GetTexture(filename);
	
	a = r = g = b = 255;
}

void CSpriteRenderer::Render(D3DXMATRIX mWorld)
{
	RECT temp;
	m_pTexture->GetImageRect(&temp);

	if (m_Sprite != NULL)
	{
		m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_Sprite->SetTransform(&mWorld);

		m_Sprite->Draw(m_pTexture->GetTexture(),
			NULL, NULL, NULL,
			D3DCOLOR_ARGB(a, r, g, b));

		m_Sprite->End();
	}
}

void CSpriteRenderer::Destroy()
{
	if (m_Sprite)
		SAFE_RELEASE(m_Sprite);
}