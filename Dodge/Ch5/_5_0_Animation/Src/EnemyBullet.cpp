#include "DXUT.h"
#include "EnemyBullet.h"

void EnemyBullet::Start()
{
	// 스프라이트 렌더러 추가
	if(!renderer)
		renderer = new CSpriteRenderer(L"EnemyBullet", L"Assets/Images/Bullet/bullet_dummy_0", L"png", false);


	fMoveSpeed = 300;
	InitPos = position;

	scale = { 0.7f, 0.7f };

	int x = rand() % 11 - 5;
	int y = rand() % 11 - 5;
	D3DXVECTOR2 vtemp(x, y);
	vMoveVector = g_pPlayer->position - position;

	D3DXVec2Normalize(&vMoveVector, &vMoveVector);        
	vMoveVector = vMoveVector + vtemp * 0.1f;

	CreateCollider(CL_BULLET, 5);
}

void EnemyBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (isHoming)
	{
		D3DXVECTOR2 vMove = g_pPlayer->position - position;
		D3DXVec2Normalize(&vMove, &vMove);
		
		vMoveVector += vMove * 2 * deltaTime;

		D3DXVec2Normalize(&vMove, &vMoveVector);
		vMoveVector = vMove;

		vMove = vMove * fMoveSpeed * deltaTime;

		position += vMove;
	}
	else
	{
		D3DXVECTOR2 vMove;
		D3DXVec2Normalize(&vMove, &vMoveVector);
		vMove = vMove * fMoveSpeed * deltaTime;
		position += vMove;
	}

	if ((position.x < 0 || position.x > 1024
		|| position.y < 0 || position.y > 768) && !isHoming)
	{
		position = InitPos;

		if (g_pPlayer)
		{
			int x = rand() % 11 - 5;
			int y = rand() % 11 - 5;
			D3DXVECTOR2 vtemp(x, y);
			vMoveVector = g_pPlayer->position - position;

			D3DXVec2Normalize(&vMoveVector, &vMoveVector);
			vMoveVector = vMoveVector + vtemp * 0.1f;
		}
	}
}