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
			D3DXVECTOR2 temp = gameObject->position - var->position;
			float length = D3DXVec2Length(&temp);

			if (length <= gameObject->radius * abs(gameObject->scale.x) + abs(var->radius * var->scale.x))
				gameObject->OnCollision(var);
		}
	}
	return 0;
}
