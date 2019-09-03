#include "DXUT.h"
#include "CWolf.h"

WolfIdle *		WolfIdle::instance = new WolfIdle;
WolfMove *		WolfMove::instance = new WolfMove;
WolfAttack *	WolfAttack::instance = new WolfAttack;
WolfJump *		WolfJump::instance = new WolfJump;
WolfFall *		WolfFall::instance = new WolfFall;
WolfHitted *	WolfHitted::instance = new WolfHitted;
WolfDown *		WolfDown::instance = new WolfDown;

CWolf::CWolf()
{
}

CWolf::~CWolf()
{
}

void CWolf::Start()
{
	type = ENEMY;

	if (!renderer)
		renderer = new CSpriteRenderer(L"Wolf", L"Assets/Images/Enemy/RedWolf_", L"png", true, 8, 21, 0.1);

	renderer->SetIndex(0, 0, 2, true);			// 0 :  0,3  - idle
	renderer->SetIndex(1, 3, 10, true);			// 1 :  3,10  - move
	renderer->SetIndex(2, 11, 12, false);		// 2 :  11,12 - jump
	renderer->SetIndex(3, 13, 13, false);		// 3 :  13,13 - fall
	renderer->SetIndex(4, 14, 14, false);		// 4 :  14,14 - falltoidle
	renderer->SetIndex(5, 15, 17, false);		// 5 :  15,17 - attack
	renderer->SetIndex(6, 18, 18, false);		// 6 :  18,18 - hit
	renderer->SetIndex(7, 18, 21, false);		// 7 :  18,21 - Down

	WolfIdle::instance->EnterState(this);

	CreateRigidBody(D3DXVECTOR2(0, 25), D3DXVECTOR2(70, 50));
	CreateCollider(CL_ENEMY, D3DXVECTOR2(0, 30), D3DXVECTOR2(80, 60));

	playerCheck = new CPlayerCheck;
	playerCheck->CreateCollider(CL_CHECK, D3DXVECTOR2(0, 20), D3DXVECTOR2(40, 40));

	platformCheck = new CPlatformCheck;
	jumpPlatformCheck = new CPlatformCheck;

	enemyAttackCollider = new CEnemyAttackCollider;
	enemyAttackCollider->CreateCollider(CL_ENEMYATTACK, D3DXVECTOR2(0, 20), D3DXVECTOR2(40, 40));
	enemyAttackCollider->parent = this;

	pivot.x = 0.7;
	pivot.y = 0.1;

	moveSpeed = 100;

	vMove = { 1,0 };
}

void CWolf::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (!platformCheck->bCheck)
		vMove.x *= -1;

	nowState->UpdateState(this, deltaTime);

	playerCheck->position = position + D3DXVECTOR2(55 * scale.x, 0);
	platformCheck->position = position + D3DXVECTOR2(50 * scale.x, -10);
	jumpPlatformCheck->position = position + D3DXVECTOR2(10 * scale.x, 150);
	enemyAttackCollider->position = position + D3DXVECTOR2(55 * scale.x, 0);
}

bool CWolf::Move(float deltaTime)
{
	if (!bGround)
		return false;

	if (!bFlip && prevMove.x * vMove.x < 0)
	{
		scale.x = prevMove.x;
		vMove.x = 0;
	}
	else
	{
		prevMove = vMove;
	}

	scale.x = prevMove.x;

	D3DXVec2Normalize(&vMove, &vMove);

	prevPos = position;
	velocity.x = vMove.x * moveSpeed;

	if (position.x < g_OpenScene->limitrect.left + 20 || position.x >g_OpenScene->limitrect.right - 20)
		position.x = prevPos.x;

	return true;
}
