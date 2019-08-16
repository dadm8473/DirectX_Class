#include "DXUT.h"
#include "Scene.h"


Scene::Scene()
{
	bNextScene = false;
	camera = { 0, 0 };
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

	vtemp = movePos - camera;

	if (D3DXVec2Length(&vtemp) < deltaTime * moveSpeed)
		camera = movePos;
	else
	{
		D3DXVec2Normalize(&vtemp, &vtemp);
		camera += vtemp * moveSpeed * deltaTime;
	}

	vtemp = camera;
	vtemp.x *= -1;
	vtemp += D3DXVECTOR2(g_Game.windowWidth * 0.5f, g_Game.windowHeight * 0.5f);

	shakeVector.x = rand() % 21 - 10;
	shakeVector.y = rand() % 21 - 10;
	D3DXVec2Normalize(&shakeVector, &shakeVector);
	vtemp += shakeVector * shakePower;

	shakeTimer += deltaTime;
	if (shakeTimer > shakeTime)
	{
		shakeTime = 0;
		shakePower = 0;
	}

	D3DXMatrixTranslation(&mCamera, vtemp.x, vtemp.y, 0);

	return 0; 
}


int Scene::MoveCamera(D3DXVECTOR2 p_pos, float p_speed)
{
	movePos = p_pos;
	moveSpeed = p_speed;

	return 0;
}

int Scene::ShakeCamera(float p_time, float p_power)
{
	shakeTime = p_time;
	shakePower = p_power;
	shakeTimer = 0;
	return 0;
}
