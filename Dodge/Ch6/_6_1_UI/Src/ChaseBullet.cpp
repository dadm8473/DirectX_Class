#include "DXUT.h"
#include "ChaseBullet.h"

void ChaseBullet::Start()
{
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"ChaseBullet", L"Assets/Images/Bullet/bullet_dummy_1", L"png", false);

	fMoveSpeed = 300;
	InitPos = position;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 0.5, 0.5 };

	g_OpenScene->CameraShake(1, 5);

	CreateCollider(CL_BULLET, 5);
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
