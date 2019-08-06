#include "DXUT.h"
#include "ChaseEnemy.h"


ChaseEnemy::ChaseEnemy(int type)
	:type(type)
{
	switch (type)
	{
	case 0:
		renderer = new CSpriteRenderer(L"ChaseEnemy1", L"Assets/Images/Boss/ChaseEnemy_", L"png", true, 2, 3, 0.5);

		renderer->SetIndex(0, 0, 1, false);
		renderer->SetIndex(1, 0, 3, false);
		break;
	case 1:
		renderer = new CSpriteRenderer(L"ChaseEnemy2", L"Assets/Images/Boss/ChaseBall_00", L"png", false);
		break;
	case 2:
		renderer = new CSpriteRenderer(L"ChaseEnemy3", L"Assets/Images/Boss/ChaseHall_00", L"png", false);
		break;
	default:
		renderer = new CSpriteRenderer(L"ChaseEnemy_Default", L"Assets/Images/Boss/ChaseEnemy_00", L"png", false);
		break;
	}
}

ChaseEnemy::~ChaseEnemy()
{
}

void ChaseEnemy::Start()
{
	// 스프라이트 렌더러 추가

	fMoveSpeed = 300;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 2, 2 };

	maxHP = 100;
	hp = 100;

	activeTimer = 0;
	activeTime = 2;

	if (type == 2)
		activeTime = 10; 

	CreateCollider(CL_ENEMY, 10 * (type + 1));
	if(type == 0 || type == 1)
		SetCollision(CL_PLAYER_BULLET);
	bCollision = true;

	colorTimer = 0;
	colorTime = 0.2;
}

void ChaseEnemy::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove;

	if (type == 0)
	{
		activeTimer += deltaTime;
		if (activeTimer > activeTime)
		{
			vMove = g_pPlayer->position - position;
			D3DXVec2Normalize(&vMove, &vMove);

			vMoveVector += vMove * 2 * deltaTime;
			bCollision = true;
		}
	}

	if (type == 1)
	{
		vMove = g_pPlayer->position - position;
		D3DXVec2Normalize(&vMove, &vMove);

		vMoveVector += vMove * 2 * deltaTime;
	}

	if (type == 2)
	{
		activeTimer += deltaTime;
		if (activeTimer > activeTime)
			bActive = false;
	}

	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMoveVector = vMove;

	vMove = vMove * fMoveSpeed * deltaTime;

	prevPos = position;
	position += vMove;

	if (position.x < -512 + 20 || position.x > 512 - 20)
	{
		prevPos = position;
		vMoveVector.x *= -1;
	}
	else if (position.y < -384 + 20 || position.y > 384 - 20)
	{
		prevPos = position;
		vMoveVector.y *= -1;
	}
	HitColorSet(deltaTime);
}

void ChaseEnemy::OnCollision(CGameObject * CollisionObject)
{
	CollisionObject->bActive = false;
	if (type == 0 || type == 1)
	{
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
}

void ChaseEnemy::HitColorSet(float deltaTime)
{
	if (type == 0 || type == 1)
	{
		if (colorTimer > colorTime)
		{
			renderer->b = 255;
			renderer->g = 255;
		}
		else
			colorTimer += deltaTime;
	}
}
