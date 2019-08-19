#include "DXUT.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	renderer = NULL;

	position = { 0, 0 };
	scale = { 1, 1 };
	pivot = { 0.5, 0.5 };
	fRot = 0;
	D3DXMatrixIdentity(&mWorld);

	g_OpenScene->m_ObjectList.push_back(this);
	g_OpenScene->m_ObjectList.sort();

	checkLayers = NULL;
	radius = 0;
	layer = -1;
}

CGameObject::~CGameObject()
{
	Destroy();
	g_OpenScene->m_ObjectList.remove(this);
}

void CGameObject::Update(float deltaTime)
{
	if (!bActive) return;

	if (!bStart)
	{
		bStart = true;
		Start();
	}

	D3DXVECTOR2 vCenter;
	if (renderer)
		vCenter = { renderer->GetTextureInfo().Width * pivot.x, renderer->GetTextureInfo().Height * pivot.y };
	else
		vCenter = { 0,0 };

	D3DXVECTOR2 pos = position;
	pos.y *= -1;
	pos -= vCenter;
	D3DXMatrixTransformation2D(&mWorld, &vCenter, 0, &scale, &vCenter,
		D3DXToRadian(fRot), &pos);

	if (renderer)
		renderer->Update(deltaTime);

	if (checkLayers)
		g_OpenScene->m_CollisionManager.Collision(this);
}

void CGameObject::Render()
{
	if (!bActive) return;

	if (type != UIOBJECT)
	{
		mWorld = mWorld * g_OpenScene->mCamera;
	}
	else
	{
		mWorld = mWorld;
	}

	if(renderer)
		renderer->Render(mWorld);
}

void CGameObject::Destroy()
{
	if (renderer)
		SAFE_DELETE(renderer);

	if (checkLayers)
	{
		delete(checkLayers);
		g_OpenScene->m_CollisionManager.colliderLists[layer].remove(this);
	}
}

void CGameObject::CreateCollider(int p_Layer, float p_Radius)
{
	if (!bActive) return;

	radius = p_Radius;

	checkLayers = new bool[CL_MAX];
	memset(checkLayers, false, CL_MAX);

	layer = p_Layer;
	g_OpenScene->m_CollisionManager.colliderLists[layer].push_back(this);
}

void CGameObject::SetCollision(int layer)
{
	checkLayers[layer] = true;
}
