#include "DXUT.h"
#include "CPlayerCheck.h"


void CPlayerCheck::Start()
{
	SetCollision(CL_PLAYER);
}

void CPlayerCheck::Update(float deltaTime)
{
	if (bCheck)
	{
		bCheck = false;
		player = NULL;
	}
	CGameObject::Update(deltaTime);
}

void CPlayerCheck::OnCollision(CGameObject * CollisionObject)
{
	bCheck = true;
	player = CollisionObject;
}

