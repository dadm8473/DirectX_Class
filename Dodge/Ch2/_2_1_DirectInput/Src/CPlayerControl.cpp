#include "DXUT.h"
#include "CPlayerControl.h"

void CPlayerControl::Start()
{
}

void CPlayerControl::Update(float deltaTime)
{
	D3DXVECTOR2 vMove(0,0);

	if (g_Input.KeyPress(VK_DOWN))
		vMove.y = 1;
	if (g_Input.KeyPress(VK_UP))
		vMove.y = -1;
	if (g_Input.KeyPress(VK_LEFT))
		vMove.x = -1;;
	if (g_Input.KeyPress(VK_RIGHT))
		vMove.x = 1;

	D3DXVec2Normalize(&vMove, &vMove);

	transform->position += vMove * fMoveSpeed * deltaTime;
}

void CPlayerControl::Destroy()
{
}
