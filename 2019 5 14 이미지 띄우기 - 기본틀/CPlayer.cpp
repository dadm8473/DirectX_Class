#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos)
{
	position = pos;
}

void CPlayer::Update(float deltatime)
{
	CMatrix::Update(deltatime);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->playerTexture);
}