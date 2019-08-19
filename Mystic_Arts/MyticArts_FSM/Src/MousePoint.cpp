#include "DXUT.h"
#include "MousePoint.h"


MousePoint::MousePoint()
{
}


MousePoint::~MousePoint()
{
}

void MousePoint::Start()
{
	type = UIOBJECT;
	CreateCollider(CL_MOUSE, D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2));
	bCollision = false;
}

void MousePoint::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (bCollision)
		bCollision = false;
}
