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

	attackEffect = new CHeroAttackEffect;
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

	attackEffect->bActive = true;
	attackEffect->position = position + D3DXVECTOR2(effectPos.x * parent->scale.x, effectPos.y);
	attackEffect->renderer->SetAni(0);

	D3DXVECTOR2 vtemp = attackVector;

	vtemp.x *= parent->scale.x;
	D3DXVec2Normalize(&vtemp, &vtemp);
	if (!CollisionObject->bGround)
	{
		CollisionObject->force.x += vtemp.x * attackPower * 0.1f;
		CollisionObject->velocity.y = vtemp.y * attackPower;
	}
	else
		CollisionObject->force += vtemp * attackPower * 0.1f;
	CollisionObject->collisionNum = collisionNum;
}
