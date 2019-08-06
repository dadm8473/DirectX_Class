#include "DXUT.h"
#include "Collider.h"

Collider::Collider(int p_Layer, float radius)
{
	CheckLayers = new bool[CL_MAX];
	memset(CheckLayers, false, sizeof(CheckLayers));

	Layer = p_Layer;
	g_OpenScene->m_CollisionManager.ColliderLists[Layer].push_back(this);
}

Collider::~Collider()
{
	g_OpenScene->m_CollisionManager.ColliderLists[Layer].remove(this);

	if (CheckLayers != NULL)
		 delete(CheckLayers); 
}
