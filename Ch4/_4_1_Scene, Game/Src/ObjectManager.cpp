#include "DXUT.h"
#include "ObjectManager.h"


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
	for each (CGameObject * var in m_ObjectList)
	{
		if (var)
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
		delete (temp);
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
