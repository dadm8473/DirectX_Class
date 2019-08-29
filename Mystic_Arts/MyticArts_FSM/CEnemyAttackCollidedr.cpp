#include "DXUT.h"
#include "CEnemyAttackCollider.h"
#include <time.h>

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

	attackEffect = new CEnemyAttackEffect;
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

	attackEffect->bActive = true;
	attackEffect->position = position + D3DXVECTOR2(effectPos.x * parent->scale.x, effectPos.y);
	srand(time(NULL));
	attackEffect->fRot += rand() % 360;
	attackEffect->renderer->SetAni(0);
	attackEffect->position = CollisionObject->position;
	attackEffect->position.y += 30;


	D3DXVECTOR2 vtemp = attackVector;

	vtemp.x *= parent->scale.x;
	D3DXVec2Normalize(&vtemp, &vtemp);
	if (!CollisionObject->bGround)
	{
		CollisionObject->force.x += vtemp.x * attackPower * 0.1;
		CollisionObject->velocity.y = vtemp.y * attackPower;
	}
	else
	{
		CollisionObject->force += vtemp * attackPower * 0.1;
	}
	CollisionObject->collisionNum = collisionNum;
}
