#include "DXUT.h"
#include "CVectorMove.h"

void CVectorMove::Start()
{
	vMoveVector = g_pPlayer->position - transform->position;
	InitPos = transform->position;
}

void CVectorMove::Update(float deltaTime)
{
	D3DXVECTOR2 vMove;
	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMove = vMove * fMoveSpeed * deltaTime;
	transform->Translate(vMove);
	
	if (transform->position.x < 0 || transform->position.x > 1024
		|| transform->position.y < 0 || transform->position.y > 768)
	{
		transform->position = InitPos;

		if (g_pPlayer)
			vMoveVector = g_pPlayer->position - transform->position;
	}
}

void CVectorMove::Destroy()
{
}
