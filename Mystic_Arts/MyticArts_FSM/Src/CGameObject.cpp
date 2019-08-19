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
	g_OpenScene->m_ObjectList.sort(ObjectSort);

	checkLayers = NULL;
	radius = 0;
	layer = -1;
}

CGameObject::CGameObject(const TCHAR * key, const TCHAR * fileName, const TCHAR * extName, bool p_bAnimation, int p_TotalIndex, int p_TotalFrame, float p_Delay)
{
	renderer = NULL;

	position = { 0, 0 };
	scale = { 1, 1 };
	pivot = { 0.5, 0.5 };
	fRot = 0;
	D3DXMatrixIdentity(&mWorld);

	g_OpenScene->m_ObjectList.push_back(this);
	g_OpenScene->m_ObjectList.sort(ObjectSort);

	checkLayers = NULL;
	radius = 0;
	layer = -1;
	renderer = new CSpriteRenderer(key, fileName, extName, p_bAnimation, p_TotalIndex, p_TotalFrame, p_Delay);
}

CGameObject::~CGameObject()
{
	Destroy();
	g_OpenScene->m_ObjectList.remove(this);
}

void CGameObject::Update(float deltaTime)
{
	if (!bStart)
	{
		bStart = true;
		Start();
	}

	D3DXVECTOR2 vCenter;
	if (renderer)
		vCenter = { renderer->GetTextureInfo().Width * pivot.x, renderer->GetTextureInfo().Height * (1 - pivot.y) };
	else
		vCenter = { 0,0 };

	D3DXVECTOR2 pos = position;

	pos.y *= -1; //★★★

	if (type == UIOBJECT) //★★★
	{
		pos.x += 512;
		pos.y += 384;
	}

	pos -= vCenter;
	D3DXMatrixTransformation2D(&mWorld, &vCenter, 0, &scale, &vCenter,
		D3DXToRadian(fRot), &pos);

	if (renderer)
		renderer->Update(deltaTime);

	if (checkLayers)
		g_OpenScene->m_CollisionManager.Collision(this);

	if (bRigidbody)
	{
		// 현재 힘에 따른 물리적 위치 이동
		if(!bGround)
			force.y -= gravity * 1.5;
		velocity += force * 10;
		velocity.x *= 0.75f;
		force = { 0,0 };
		fixedPos = position;
		position += velocity * deltaTime;

		// 플랫폼과 충돌했는지 검사
		bGround = g_OpenScene->m_CollisionManager.RigidbodyCollision(this);
	}
}

void CGameObject::Render()
{
	if (!bActive) return;

	if (type != UIOBJECT)
	{
		mWorld = mWorld * g_OpenScene->mCamera;
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
	bCollision = true;

	radius = p_Radius;

	checkLayers = new bool[CL_MAX];
	memset(checkLayers, false, CL_MAX);

	layer = p_Layer;
	g_OpenScene->m_CollisionManager.colliderLists[layer].push_back(this);
}

void CGameObject::CreateCollider(int p_Layer, D3DXVECTOR2 offset, D3DXVECTOR2 scale)
{
	bCollision = true;

	colliderOffset = offset;
	colliderScale = scale;

	checkLayers = new bool[CL_MAX];
	memset(checkLayers, false, CL_MAX);

	layer = p_Layer;
	g_OpenScene->m_CollisionManager.colliderLists[layer].push_back(this);
}

void CGameObject::SetCollision(int layer)
{
	checkLayers[layer] = true;
}

void CGameObject::CreateRigidBody(D3DXVECTOR2 offset, D3DXVECTOR2 scale)
{
	gravity = 1;
	bRigidbody = true;

	rigidboydOffset = offset;
	rigidboydScale = scale;

	g_OpenScene->m_CollisionManager.rigidbodyList.push_back(this);
}
