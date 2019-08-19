#include "DXUT.h"
#include "Scene.h"


Scene::Scene()
{
	bNextScene = false;
	camera = { 512,384 };
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

	D3DXVECTOR2 vtemp;

	shakeVector.x = rand() % 21 - 10;
	shakeVector.y = rand() % 21 - 10;
	D3DXVec2Normalize(&shakeVector, &shakeVector);
	vtemp = camera + shakeVector * shakePower;

	shakeTimer += deltaTime;
	if (shakeTimer > shakeTime)
	{
		shakeTime = 0;
		shakePower = 0;
	}

	D3DXMatrixTranslation(&mCamera, vtemp.x, vtemp.y, 0);

	return 0; 
}


int Scene::CameraShake(float p_time, float p_power)
{
	shakeTime = p_time;
	shakePower = p_power;
	shakeTimer = 0;
	return 0;
}
