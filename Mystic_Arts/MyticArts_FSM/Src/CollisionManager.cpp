#include "DXUT.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
	colliderLists = new list<CGameObject*>[CL_MAX];
}

CollisionManager::~CollisionManager()
{
	delete[](colliderLists);
}

bool CollisionManager::Collision(CGameObject * gameObject)
{
	for (int i = 0; i < CL_MAX; ++i)
	{
		if (!gameObject->checkLayers[i])
			continue;

		for each(CGameObject * var in colliderLists[i])
		{
			if (!gameObject->bActive || !gameObject->bCollision)
				return false;

			if (!var->bActive || !var->bCollision)
				continue;

			if (gameObject == var && gameObject->checkLayers[var->layer])
				continue;

			// 원, 원 충돌 판정
			//D3DXVECTOR2 temp = gameObject->position - var->position;
			//float length = D3DXVec2Length(&temp);

			//if (length <= gameObject->radius * abs(gameObject->scale.x) + abs(var->radius * var->scale.x))
			//	gameObject->OnCollision(var);
			
			// 사각형(RECT) 충돌검사
			D3DXVECTOR2 vtemp = gameObject->position + gameObject->colliderOffset;

			RECT tempRect, rect1, rect2;
			SetRect(&rect1,
				vtemp.x - gameObject->colliderScale.x * 0.5f,
				vtemp.y - gameObject->colliderScale.y * 0.5f,
				vtemp.x + gameObject->colliderScale.x * 0.5f,
				vtemp.y + gameObject->colliderScale.y * 0.5f
			);
			vtemp = var->position + var->colliderOffset;

			SetRect(&rect2,
				vtemp.x - var->colliderScale.x * 0.5f,
				vtemp.y - var->colliderScale.y * 0.5f,
				vtemp.x + var->colliderScale.x * 0.5f,
				vtemp.y + var->colliderScale.y * 0.5f
			);

			if (IntersectRect(&tempRect, &rect1, &rect2))
			{
				gameObject->OnCollision(var);
			}
		}
	}
	return 0;
}

bool CollisionManager::RigidbodyCollision(CGameObject * gameObject)
{
	if (gameObject->type == PLATFORM)
		return false;

	bool ground = false;

	for each(CGameObject * var in rigidbodyList)
	{
		if (!gameObject->bActive || !gameObject->bRigidbody)
			return ground;

		if (!var->bActive || !var->bRigidbody || var == gameObject)
			continue;

		// 사각형(RECT) 충돌검사
		D3DXVECTOR2 vtemp = gameObject->position + gameObject->rigidboydOffset;

		RECT tempRect, rect1, rect2;
		SetRect(&rect1,
			vtemp.x - gameObject->rigidboydScale.x * abs(gameObject->scale.x) * 0.5f,
			vtemp.y - gameObject->rigidboydScale.y * 0.5f,
			vtemp.x + gameObject->rigidboydScale.x * abs(gameObject->scale.x) * 0.5f,
			vtemp.y + gameObject->rigidboydScale.y * 0.5f
		);
		vtemp = var->position + var->rigidboydOffset;

		SetRect(&rect2,
			vtemp.x - var->rigidboydScale.x * 0.5f,
			vtemp.y - var->rigidboydScale.y * 0.5f,
			vtemp.x + var->rigidboydScale.x * 0.5f,
			vtemp.y + var->rigidboydScale.y * 0.5f
		);

		if (IntersectRect(&tempRect, &rect1, &rect2))
		{
			// 콜라이더 충돌
			if (var->type == PLATFORM && gameObject->velocity.y <= 0
				&& gameObject->fixedPos.y >= rect2.bottom - 1)
			{
				ground = true;
				gameObject->position.y = gameObject->fixedPos.y = rect2.bottom - 1;
				gameObject->velocity.y = 0;
				gameObject->velocity *= 0.5f;
			}
		}
	}
	return ground;
}
