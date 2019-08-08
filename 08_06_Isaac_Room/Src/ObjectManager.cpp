#include "DXUT.h"
#include "ObjectManager.h"

bool ObjectSort(const CGameObject* lhs, const CGameObject* rhs)
{
	return lhs->type < rhs->type;
}

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

int ObjectManager::Start()
{
	for each (CGameObject * var in m_ObjectList)
	{
		if(var)
			var->Start();
	}
	return 0;
}

int ObjectManager::Update(float deltaTime)
{
	m_ObjectList.sort(ObjectSort);
	for each (CGameObject * var in m_ObjectList)
	{
		if (var && var->bActive)
			var->Update(deltaTime);
	}
	return 0;
}

int ObjectManager::Destroy()
{
	for (std::list<CGameObject*>::iterator it = m_ObjectList.begin(); it != m_ObjectList.end();)
	{
		CGameObject * temp = *it;
		it = m_ObjectList.erase(it);
		SAFE_DELETE(temp);
	}

	return 0;
}

int ObjectManager::Render()
{
	for each (CGameObject * var in m_ObjectList)
	{
		if (var)
			var->Render();
	}
	return 0;
}
