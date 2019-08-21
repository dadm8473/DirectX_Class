#include "DXUT.h"
#include "CGolem.h"

GolemIdle * GolemIdle::instance = new GolemIdle;
GolemMove * GolemMove::instance = new GolemMove;
GolemAttack1 * GolemAttack1::instance = new GolemAttack1;
GolemAttack2 * GolemAttack2::instance = new GolemAttack2;

void CGolem::Start()
{
	if (!renderer)
		renderer = new CSpriteRenderer(L"Golem", L"Assets/Images/Enemy/BlueGolem_", L"png", true, 6, 28, 0.06);

	renderer->SetIndex(0, 0, 0, false);			// 0 :  0,4  - idle
	renderer->SetIndex(1, 1, 8, true);			// 1 :  5,9  - move
	renderer->SetIndex(2, 9, 11, false);		// 2 :  9,11 - attack1 stay
	renderer->SetIndex(3, 12, 16, false);		// 3 : 12,16 - attack1
	renderer->SetIndex(4, 17, 20, false);		// 4 : 17,20 - attack2 stay
	renderer->SetIndex(5, 21, 25, false);		// 4 : 21,25 - attack2 

	GolemIdle::instance->EnterState(this);

	enemyAttackCollider = new CEnemyAttackCollider;
	enemyAttackCollider->parent = this;

	CreateRigidBody(D3DXVECTOR2(0, 60), D3DXVECTOR2(80, 120));
	CreateCollider(CL_ENEMY, D3DXVECTOR2(0, 60), D3DXVECTOR2(80, 120));

	playerCheck = new CPlayerCheck;
	playerCheck->CreateCollider(CL_CHECK, D3DXVECTOR2(0, 50), D3DXVECTOR2(200, 100));

	platformCheck = new CPlatformCheck;

	pivot.x = 0.8;
	pivot.y = -0.6;

	moveSpeed = 100;

	mass = 10;

	vMove = { 1,0 };
}

void CGolem::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (!platformCheck->bCheck)
		vMove.x *= -1;

	nowState->UpdateState(this, deltaTime);

	playerCheck->position = position + D3DXVECTOR2(30 * scale.x, 0);
	platformCheck->position = position + D3DXVECTOR2(50 * scale.x, -10);
}

bool CGolem::Move(float deltaTime)
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
	position += vMove * moveSpeed * deltaTime;

	if (position.x < g_OpenScene->limitrect.left + 20 || position.x >g_OpenScene->limitrect.right - 20)
		position.x = prevPos.x;

	return true;
}

