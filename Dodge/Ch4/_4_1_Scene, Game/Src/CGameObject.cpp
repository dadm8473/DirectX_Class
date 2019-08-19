#include "DXUT.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	g_OpenScene->m_ObjectList.push_back(this);
}

CGameObject::~CGameObject()
{
	Destroy();
	g_OpenScene->m_ObjectList.remove(this);
}

void CGameObject::Start()
{
	Init();

	for each (IComponent * var in Components)
	{
		var->Start();
	}
	CTransform::Start();
}

void CGameObject::Update(float deltaTime)
{
	if (!m_bStart)
	{
		m_bStart = true;
		Start();
	}

	for each (IComponent * var in Components)
	{
		var->Update(deltaTime);
	}
	CTransform::Update(deltaTime);
}

void CGameObject::Render()
{
	if(m_Renderer != nullptr)
		m_Renderer->Render(mWorld);
}

void CGameObject::Destroy()
{
	if (m_Renderer != nullptr)
		m_Renderer->Destroy();

	for each (IComponent * var in Components)
	{
		var->Destroy();
	}
	CTransform::Destroy();
}
