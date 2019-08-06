#include "DXUT.h"
#include "CVectorMove.h"

void CVectorMove::Start()
{
	/*int x = rand() % 11 - 5;
	int y = rand() % 11 - 5;
	D3DXVECTOR2 vtemp(x, y);
	vMoveVector = g_pPlayer->position - transform->position;

	D3DXVec2Normalize(&vMoveVector, &vMoveVector);
	vMoveVector = vMoveVector + vtemp * 0.1f;

	InitPos = transform->position;*/
}

void CVectorMove::Update(float deltaTime)
{
	/*D3DXVECTOR2 vMove;
	D3DXVec2Normalize(&vMove, &vMoveVector);
	vMove = vMove * fMoveSpeed * deltaTime;
	transform->Translate(vMove);
	
	if (transform->position.x < 0 || transform->position.x > 1024
		|| transform->position.y < 0 || transform->position.y > 768)
	{
		transform->position = InitPos;

		if (g_pPlayer)
		{
			int x = rand() % 11 - 5;
			int y = rand() % 11 - 5;
			D3DXVECTOR2 vtemp(x, y);
			vMoveVector = g_pPlayer->position - transform->position;

			D3DXVec2Normalize(&vMoveVector, &vMoveVector);
			vMoveVector = vMoveVector + vtemp * 0.1f;
		}
	}*/

	transform->position.x += sin(fAngle*(D3DX_PI / 180))*fMoveSpeed*deltaTime;
	transform->position.y -= cos(fAngle*(D3DX_PI / 180))*fMoveSpeed*deltaTime;

	if (transform->position.x < 0 || transform->position.x > 1024
		|| transform->position.y < 0 || transform->position.y > 768)
	{
		/*transform = NULL;
		delete this;*/
		transform->Destroy();
	}
}

void CVectorMove::Destroy()
{
}
