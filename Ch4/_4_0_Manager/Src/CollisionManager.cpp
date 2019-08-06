#include "DXUT.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
	ColliderLists = new list<Collider*>[CL_MAX];
}

CollisionManager::~CollisionManager()
{
	delete[](ColliderLists);
}

bool CollisionManager::Collision(Collider * p_Collider)
{
	for (int i = 0; i < CL_MAX; ++i)
	{
		if (!p_Collider->CheckLayers[i])
			continue;

		for each(Collider * var in ColliderLists[i])
		{
			if (p_Collider == var && p_Collider->CheckLayers[var->Layer])
				continue;

			if (p_Collider->Type != var->Type)
			{
				// 원, 사각형 충돌 판정
				D3DXVECTOR2 vScale = var->scale + p_Collider->scale;
				D3DXVECTOR2 LeftTop;
				D3DXVECTOR2 RightBottom;
				if (p_Collider->Type == CT_CIRCLE)
				{
					LeftTop = var->transform->position - vScale;
					RightBottom = var->transform->position + vScale;

					if (LeftTop.x <= p_Collider->transform->position.x
						&& LeftTop.y <= p_Collider->transform->position.y
						&& RightBottom.x >= p_Collider->transform->position.x
						&& RightBottom.y >= p_Collider->transform->position.y)
						p_Collider->OnCollision(var->transform);
				}
				else if (p_Collider->Type == CT_BOX)
				{
					LeftTop = p_Collider->transform->position - vScale;
					RightBottom = p_Collider->transform->position + vScale;

					if (LeftTop.x <= var->transform->position.x
						&& LeftTop.y <= var->transform->position.y
						&& RightBottom.x >= var->transform->position.x
						&& RightBottom.y >= var->transform->position.y)
						p_Collider->OnCollision(var->transform);
				}


			}
			else if (p_Collider->Type == CT_CIRCLE)
			{
				// 원, 원 충돌 판정
				D3DXVECTOR2 temp = p_Collider->transform->position - var->transform->position;
				float length = D3DXVec2Length(&temp);

				if (length <= p_Collider->scale.x + var->scale.x)
					p_Collider->OnCollision(var->transform);
			}
			else if (p_Collider->Type == CT_BOX)
			{
				RECT rect_var =
				{
					(var->transform->position - var->scale).x,
					(var->transform->position - var->scale).y,
					(var->transform->position + var->scale).x,
					(var->transform->position + var->scale).y,

				};
				RECT rect_Collider =
				{
					(p_Collider->transform->position - p_Collider->scale).x,
					(p_Collider->transform->position - p_Collider->scale).y,
					(p_Collider->transform->position + p_Collider->scale).x,
					(p_Collider->transform->position + p_Collider->scale).y,
				};
				RECT temp;

				if(IntersectRect(&temp, &rect_Collider, &rect_var))
					p_Collider->OnCollision(var->transform);
			}
		}
	}
	return 0;
}
