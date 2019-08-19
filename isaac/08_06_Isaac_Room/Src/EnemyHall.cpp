#include "DXUT.h"
#include "EnemyHall.h"


EnemyHall::EnemyHall()
{
}


EnemyHall::~EnemyHall()
{
}

void EnemyHall::Start()
{
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"EnemyHall", L"Assets/Images/Boss/EnemyHall", L"png", false);

	fMoveSpeed = 500;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 2, 2 };

	CreateCollider(CL_ENEMY, 15);
	SetCollision(CL_PLAYER_BULLET);

	Timer = 0;
	Time = 10;
}

void EnemyHall::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove;

	D3DXVec2Normalize(&vMove, &vMoveVector);

	vMove = vMove * fMoveSpeed * deltaTime;

	prevPos = position;
	position += vMove;

	if (position.x < g_OpenScene->limitrect.left + 50)
	{
		prevPos = position;
		vMoveVector.x = abs(vMoveVector.x);
	}
	else if (position.x > g_OpenScene->limitrect.right - 50)
	{
		prevPos = position;
		vMoveVector.x = -abs(vMoveVector.x);
	}
	else if (position.y < g_OpenScene->limitrect.top + 50)
	{
		prevPos = position;
		vMoveVector.y = abs(vMoveVector.y);
	}
	else if (position.y > g_OpenScene->limitrect.bottom - 50)
	{
		prevPos = position;
		vMoveVector.y = -abs(vMoveVector.y);
	}

	Timer += deltaTime;
	if (Timer > Time)
	{
		Timer = 0;
		bActive = false;
	}
	
}