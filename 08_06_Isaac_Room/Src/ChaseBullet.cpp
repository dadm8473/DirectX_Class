#include "DXUT.h"
#include "ChaseBullet.h"

void ChaseBullet::Start()
{
	type = ENEMY_BULLET;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"ChaseBullet", L"Assets/Images/Bullet/Enemy_Tear", L"png", false);

	fMoveSpeed = 300;
	InitPos = position;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 2, 2 };

	CreateCollider(CL_ENEMY_BULLET, 5);
	timer = 0;
}

void ChaseBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	timer += deltaTime;

	if (timer > 3)
		bActive = false;

	D3DXVECTOR2 vMove = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMove, &vMove);
	
	vMoveVector += vMove * 2 * deltaTime;

	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMoveVector = vMove;

	vMove = vMove * fMoveSpeed * deltaTime;
	
	position += vMove;
}
