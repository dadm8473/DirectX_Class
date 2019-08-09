#include "DXUT.h"
#include "ChaseBullet.h"

void ChaseBullet::Start()
{
	type = ENEMY_BULLET;
	// ��������Ʈ ������ �߰�
	renderer = new CSpriteRenderer(L"ChaseBullet", L"Assets/Images/Bullet/Enemy_Tear", L"png", false);

	fMoveSpeed = 300;
	InitPos = position;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 1, 1 };

	CreateCollider(CL_ENEMY_BULLET, 5);
}

void ChaseBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMove, &vMove);
	
	vMoveVector += vMove * 2 * deltaTime;

	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMoveVector = vMove;

	vMove = vMove * fMoveSpeed * deltaTime;
	
	position += vMove;
}