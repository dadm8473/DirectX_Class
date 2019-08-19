#pragma once

class Scene : public ObjectManager
{
public:
	RECT limitrect = { -512,384,512,-384 };

	D3DXMATRIX mCamera;
	D3DXVECTOR2 camera;

	D3DXVECTOR2 movePos = { 0,0 };
	float moveSpeed = 0;

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

	int MoveCamera(D3DXVECTOR2 p_pos, float p_speed);
	int ShakeCamera(float p_time, float p_power);
};

