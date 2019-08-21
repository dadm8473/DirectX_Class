#include "DXUT.h"
#include "CPlatformCheck.h"

void CPlatformCheck::Start()
{
	CreateCollider(CL_CHECK, D3DXVECTOR2(0, 0), D3DXVECTOR2(10, 10));
	SetCollision(CL_PLATFORM);
}

void CPlatformCheck::Update(float deltaTime)
{
	if (bCheck)
	{
		bCheck = false;
		checkedPlatform = NULL;
	}
	CGameObject::Update(deltaTime);
}

void CPlatformCheck::OnCollision(CGameObject * CollisionObject)
{
	bCheck = true;
	checkedPlatform = (Platform*)CollisionObject;
}
