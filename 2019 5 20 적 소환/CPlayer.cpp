#include "DXUT.h"
#include "Header.h"
#include "CPlayer.h"

CPlayer::CPlayer(D3DXVECTOR2 pos)
	: CMatrix(), attackTimer(0), attackTime(0.05f), isAttacking(false)
{
	position = pos;
	center = D3DXVECTOR2(50, 50);
	SetAnimation(0.3f, 3, true);
}

void CPlayer::Update(float deltatime)
{
	CMatrix::Update(deltatime);

	attackTimer += deltatime;
	if (isAttacking)
	{
		if (attackTimer > attackTime)
		{
			attackTimer = 0;

			// 부모 씬 플레이어 총알 리스트 push back
			parentScene->playerBulletList.push_back(new CBullet(position, 1024, 0));

			isAttacking = false;
		}
	}
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->playerTexture);
}

void CPlayer::Attack()
{
	isAttacking = true;
}
