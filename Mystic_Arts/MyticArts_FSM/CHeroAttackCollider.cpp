#include "DXUT.h"
#include "CHeroAttackCollider.h"


CHeroAttackCollider::CHeroAttackCollider()
{
}


CHeroAttackCollider::~CHeroAttackCollider()
{
}

void CHeroAttackCollider::Start()
{
	CreateCollider(CL_PLAYERATTACK, D3DXVECTOR2(0, 30), D3DXVECTOR2(40, 60));
	SetCollision(CL_ENEMY);

	attackVector = { 0,0 };
	attackPower = 0;
	bCollision = false;
}

void CHeroAttackCollider::Update(float deltaTime)
{
	position = parent->position + D3DXVECTOR2(25 * parent->scale.x, 0);

	CGameObject::Update(deltaTime);
}

void CHeroAttackCollider::OnCollision(CGameObject * CollisionObject)
{
	if (CollisionObject->collisionNum == collisionNum)
		return;

	D3DXVECTOR2 vtemp = attackVector;

	vtemp.x *= parent->scale.x;
	D3DXVec2Normalize(&vtemp, &vtemp);
	CollisionObject->velocity = vtemp * attackPower;
	CollisionObject->collisionNum = collisionNum;
}
