#pragma once

class Scene : public ObjectManager
{
public:
	D3DXMATRIX mCamera;
	D3DXVECTOR2 camera;

	D3DXVECTOR2 shakeVector;
	float shakeTimer = 0;
	float shakeTime = 0;
	float shakePower = 0;

	bool bNextScene;

	CollisionManager m_CollisionManager;

	Scene();
	~Scene();

	virtual int Start();

	virtual int Update(float deltaTime);

	virtual int Render();

	virtual int Destroy();

	int CameraShake(float p_time, float p_power);

	//virtual int Command(CGameObject* p_Source, bool pushUp, DWORD lParam);
};

