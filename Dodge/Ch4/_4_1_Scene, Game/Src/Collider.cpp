#include "DXUT.h"
#include "Collider.h"

Collider::Collider(CGameObject * p_trnasform, int p_Layer) : Component(p_trnasform)
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
void Collider::Update(float deltaTime)
{
	g_OpenScene->m_CollisionManager.Collision(this);
}
