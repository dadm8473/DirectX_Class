#include "DXUT.h"
#include "ChaseEnemy.h"


ChaseEnemy::ChaseEnemy()
{
}


ChaseEnemy::~ChaseEnemy()
{
}

void ChaseEnemy::Start()
{
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"ChaseEnemy", L"Assets/Images/Boss/ChaseEnemy_", L"png", true, 2, 3, 0.5);

	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(1, 0, 3, false);
	renderer->a = 180;

	fMoveSpeed = 300;

	vMoveVector = g_pPlayer->position - position;
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	scale = { 2, 2 };

	maxHP = 100;
	hp = 100;

	activeTimer = 0;
	activeTime = 2;

	CreateCollider(CL_ENEMY, 10);
	SetCollision(CL_PLAYER_BULLET);
	bCollision = false;

	colorTimer = 0;
	colorTime = 0.2;
}

void ChaseEnemy::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	if (!bActive)
		return;

	D3DXVECTOR2 vMove;

	activeTimer += deltaTime;
	if (activeTimer > activeTime) 
	{
		activeTimer = 0;

		if (!bCollision)
		{
			renderer->a = 255;
			bCollision = true;
		}
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				EnemyBullet * temp = new EnemyBullet;
				temp->position = position;
				temp->vMoveVector = g_pPlayer->position - position;

				D3DXMATRIX mtemp;
				D3DXMatrixRotationZ(&mtemp, D3DXToRadian(30 - 30 * i));
				D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
			}
		}
	}

	if (bCollision)
	{
		vMove = g_pPlayer->position - position;
		D3DXVec2Normalize(&vMove, &vMove);

		vMoveVector += vMove * 2 * deltaTime;
	}

	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMoveVector = vMove;

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
	HitColorSet(deltaTime);
}

void ChaseEnemy::OnCollision(CGameObject * CollisionObject)
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

void ChaseEnemy::HitColorSet(float deltaTime)
{
	if (colorTimer > colorTime)
	{
		renderer->b = 255;
		renderer->g = 255;
	}
	else
		colorTimer += deltaTime;
}
