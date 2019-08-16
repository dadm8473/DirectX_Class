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
	CreateCollider(CL_MOUSE, 3);
	bCollision = false;
}

void MousePoint::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (bCollision)
		bCollision = false;
}
