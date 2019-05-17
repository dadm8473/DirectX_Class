#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos)
{
	position = pos;
	center = D3DXVECTOR2(50, 50);
	SetAnimation(0.3f, 3, true);
}

void CPlayer::Update(float deltatime)
{
	CMatrix::Update(deltatime);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->playerTexture);
}