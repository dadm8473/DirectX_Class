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

	scale = { 2, 2 };

	CreateCollider(CL_PLAYER_BULLET, 5);
}

void PlayerBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove;
	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMove = vMove * fMoveSpeed * deltaTime;
	position += vMove;

	if ((position.x < -512 || position.x > 512
		|| position.y < -384 || position.y > 384))
	{
		bActive = false;
	}
}
