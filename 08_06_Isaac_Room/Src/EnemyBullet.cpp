#include "DXUT.h"
#include "EnemyBullet.h"

void EnemyBullet::Start()
{
	type = ENEMY_BULLET;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"EnemyBullet", L"Assets/Images/Bullet/Enemy_Tear", L"png", false);

	InitPos = position;

	//int x = rand() % 11 - 5;
	//int y = rand() % 11 - 5;
	//D3DXVECTOR2 vtemp(x, y);
	//vMoveVector = g_pPlayer->position - position;

	//D3DXVec2Normalize(&vMoveVector, &vMoveVector);
	//vMoveVector = vMoveVector + vtemp * 0.1f;

	scale = { 2, 2 };

	CreateCollider(CL_ENEMY_BULLET, 5);
}

void EnemyBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove;
	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMove = vMove * fMoveSpeed * deltaTime;
	position += vMove;

	if ((position.x < g_OpenScene->limitrect.left + 50 || position.x >g_OpenScene->limitrect.right - 50
		|| position.y < g_OpenScene->limitrect.top + 50 || position.y > g_OpenScene->limitrect.bottom - 50))
	{
		bActive = false;
		//position = InitPos;

		//if (g_pPlayer)
		//{
		//	int x = rand() % 11 - 5;
		//	int y = rand() % 11 - 5;
		//	D3DXVECTOR2 vtemp(x, y);
		//	vMoveVector = g_pPlayer->position - position;

		//	D3DXVec2Normalize(&vMoveVector, &vMoveVector);
		//	vMoveVector = vMoveVector + vtemp * 0.1f;
		//}
	}
}