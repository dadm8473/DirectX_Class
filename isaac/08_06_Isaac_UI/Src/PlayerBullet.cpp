#include "DXUT.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Start()
{
	type = PLAYER_BULLET;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"PlayerBullet", L"Assets/Images/Bullet/Isaac_Tear", L"png", false);

	fMoveSpeed = 500;

	scale = D3DXVECTOR2((float)bullet_damage / 2.5, (float)bullet_damage / 2.5);

	CreateCollider(CL_PLAYER_BULLET, 5);
}

void PlayerBullet::Update(float deltaTime)
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
	}
}
