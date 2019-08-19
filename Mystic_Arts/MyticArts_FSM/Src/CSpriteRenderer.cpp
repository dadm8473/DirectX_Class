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
		lastFrame = new int[p_TotalIndex];

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

		if(nowFrame < lastFrame[nowIndex])
			nowFrame++;
		else if (roop[nowIndex])
		{
			nowFrame = startFrame[nowIndex];
		}
		else
		{
			bAnimation = false;
		}
	}
}


void CSpriteRenderer::Render(D3DXMATRIX mWorld)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

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
		SAFE_DELETE_ARRAY(lastFrame);
	}

	if (rect)
		SAFE_DELETE(rect);
}

void CSpriteRenderer::SetIndex(int p_index, int p_startFrame, int p_lastFrame, bool p_roop)
{
	roop[p_index] = p_roop;
	startFrame[p_index] = p_startFrame;
	lastFrame[p_index] = p_lastFrame;
}

void CSpriteRenderer::SetAni(int index)
{
	bAnimation = true;
	nowIndex = index;
	nowFrame = startFrame[nowIndex];
}
