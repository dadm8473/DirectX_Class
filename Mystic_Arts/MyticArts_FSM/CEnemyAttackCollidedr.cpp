#include "DXUT.h"
#include "CEnemyAttackCollider.h"

CEnemyAttackCollider::CEnemyAttackCollider()
{
}


CEnemyAttackCollider::~CEnemyAttackCollider()
{
}

void CEnemyAttackCollider::Start()
{
	CreateCollider(CL_ENEMYATTACK, D3DXVECTOR2(0, 50), D3DXVECTOR2(250, 150));
	SetCollision(CL_PLAYER);

	attackVector = { 0,0 };
	attackPower = 0;
	bCollision = false;
}

void CEnemyAttackCollider::Update(float deltaTime)
{
	position = parent->position + D3DXVECTOR2(25 * parent->scale.x, 0);

	CGameObject::Update(deltaTime);
}

void CEnemyAttackCollider::OnCollision(CGameObject * CollisionObject)
{
	if (CollisionObject->collisionNum == collisionNum)
		return;

	D3DXVECTOR2 vtemp = attackVector;

	vtemp.x *= parent->scale.x;
	D3DXVec2Normalize(&vtemp, &vtemp);
	CollisionObject->force = vtemp * attackPower * 0.1f;
	CollisionObject->collisionNum = collisionNum;
}
