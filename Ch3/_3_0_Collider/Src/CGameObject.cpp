#include "DXUT.h"
#include "CGameObject.h"

void CGameObject::Start()
{
	Init();

	for each (IComponent * val in Components)
	{
		val->Start();
	}
	CTransform::Start();
}

void CGameObject::Update(float deltaTime)
{
	for each (IComponent * val in Components)
	{
		val->Update(deltaTime);
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

	for each (IComponent * val in Components)
	{
		val->Destroy();
	}
	CTransform::Destroy();
}
