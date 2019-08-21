#pragma once
class CGameObject
{
public:
	bool bActive = true;
	bool bStart = false;

	int type = GAMEOBJECT;

	// animation 및 render 관련 변수
	CSpriteRenderer * renderer;

	// world transform 변수
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 pivot;
	float fRot;
	D3DXMATRIX mWorld;

	// 충돌 체크 관련 변수
	bool bCollision = false;
	int layer;
	float radius;
	D3DXVECTOR2 colliderOffset;
	D3DXVECTOR2 colliderScale;
	bool* checkLayers;

	// 물리구현을 위한 변수
	bool bRigidbody = false;
	bool bGround = false;
	D3DXVECTOR2 rigidboydOffset;
	D3DXVECTOR2 rigidboydScale;
	float gravity = 0;
	float mass = 1;
	D3DXVECTOR2 force = { 0,0 };
	D3DXVECTOR2 velocity = { 0,0 };

	D3DXVECTOR2 fixedPos;

	int collisionNum = 0;

public:
	CGameObject();
	CGameObject(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, bool p_bAnimation, int p_TotalIndex = 0, int p_TotalFrame = 0, float p_Delay = 0);
	virtual ~CGameObject();

	virtual void Start() {};
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

	void CreateCollider(int layer, float radius);
	void CreateCollider(int layer, D3DXVECTOR2 offset, D3DXVECTOR2 scale);
	void SetCollision(int layer);

	void CreateRigidBody(D3DXVECTOR2 offset, D3DXVECTOR2 scale);

	virtual void OnCollision(CGameObject* CollisionObject) {};
};