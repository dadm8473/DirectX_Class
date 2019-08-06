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
	for each (CGameObject * var in m_ObjectList)
	{
		if (var)
			var->Destroy();
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
