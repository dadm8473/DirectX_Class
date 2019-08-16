#include "DXUT.h"
#include "CSpriteRenderer.h"

CSpriteRenderer::CSpriteRenderer(const TCHAR* key, const TCHAR* filename, const TCHAR * extname, bool p_bAnimation, int p_TotalIndex, int p_TotalFrame, float p_Delay)
{
	if (FAILED(D3DXCreateSprite(DXUTGetD3D9Device(), &sprite)))
	{
		MessageBox(DXUTGetHWND(), L"Err: Sprite Create", L"Err", MB_OK);
		return;
	}

	bAnimation = p_bAnimation;
	delay = p_Delay;
	nowIndex = 0;
	nowFrame = 0;
	delayTimer = 0;

	if (!bAnimation)
	{
		pTexture = g_Game.m_ResourceManager.GetTexture(key, filename, extname);
	}
	else
	{
		roop = new bool[p_TotalIndex];
		startFrame = new int[p_TotalIndex];
		frameAmount = new int[p_TotalIndex];

		pTexture = g_Game.m_ResourceManager.GetTexture(key, filename, extname, p_TotalFrame);
	}

	a = r = g = b = 255;
	rect = NULL;
}

void CSpriteRenderer::Update(float deltaTime)
{
	if (!bAnimation)
		return;

	delayTimer += deltaTime;
	if (delayTimer > delay)
	{
		delayTimer = 0;

		nowFrame++;
		if (nowFrame > startFrame[nowIndex] + frameAmount[nowIndex] - 1)
			if (roop[nowIndex])
				nowFrame = startFrame[nowIndex];
			else
			{
				nowFrame--;
				bAnimation = false;
			}
	}
}


void CSpriteRenderer::Render(D3DXMATRIX mWorld)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->SetTransform(&mWorld);

	sprite->Draw(pTexture->m_pTex[nowFrame],
		rect ? rect : NULL, NULL, NULL,
		D3DCOLOR_ARGB(a, r, g, b));

	sprite->End();
}

void CSpriteRenderer::Destroy()
{
	if (sprite)
		SAFE_RELEASE(sprite);

	if (delay != 0)
	{
		SAFE_DELETE_ARRAY(startFrame);
		SAFE_DELETE_ARRAY(frameAmount);
	}

	if (rect)
		SAFE_DELETE(rect);
}

void CSpriteRenderer::SetIndex(int p_index, int p_startFrame, int p_frameAmount, bool p_roop)
{
	roop[p_index] = p_roop;
	startFrame[p_index] = p_startFrame;
	frameAmount[p_index] = p_frameAmount;
}

void CSpriteRenderer::SetAni(int index)
{
	bAnimation = true;
	nowIndex = index;
	nowFrame = startFrame[nowIndex];
}
