#include "DXUT.h"
#include "ChaseBall.h"


ChaseBall::ChaseBall()
{
}


ChaseBall::~ChaseBall()
{
}

void ChaseBall::Start()
{
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"ChaseBall", L"Assets/Images/Boss/ChaseBall", L"png", false);

	fMoveSpeed = 300;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 2, 2 };

	maxHP = 100;
	hp = 100;

	CreateCollider(CL_ENEMY, 10);
	SetCollision(CL_PLAYER_BULLET);

	colorTimer = 0;
	colorTime = 0.2;
}

void ChaseBall::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove;

	vMove = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMove, &vMove);

	vMoveVector += vMove * 4 * deltaTime;

	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMoveVector = vMove;

	vMove = vMove * fMoveSpeed * deltaTime;

	prevPos = position;
	position += vMove;

	HitColorSet(deltaTime);
}

void ChaseBall::OnCollision(CGameObject * CollisionObject)
{
	CollisionObject->bActive = false;
	hp -= 34;
	if (hp < 0)
	{
		bActive = false;
	}
	else
	{
		colorTimer = 0;
		renderer->b = 50;
		renderer->g = 50;
	}
}

void ChaseBall::HitColorSet(float deltaTime)
{
	if (colorTimer > colorTime)
	{
		renderer->b = 255;
		renderer->g = 255;
	}
	else
		colorTimer += deltaTime;
}
