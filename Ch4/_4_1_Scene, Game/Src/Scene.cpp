#include "DXUT.h"
#include "Scene.h"


Scene::Scene()
{
	bNextScene = false;
}
Scene::~Scene() 
{

}

int Scene::Start()
{
	if (g_OpenScene)
		g_OpenScene->Destroy();

	g_OpenScene = this;
	ObjectManager::Start(); 
	return 0;
}

int Scene::Destroy()
{
	ObjectManager::Destroy(); 

	delete(this);
	
	return 0;
}

int Scene::Render() 
{
	ObjectManager::Render(); 
	return 0; 
}

int Scene::Update(float deltaTime)
{
	ObjectManager::Update(deltaTime);
	return 0; 
}