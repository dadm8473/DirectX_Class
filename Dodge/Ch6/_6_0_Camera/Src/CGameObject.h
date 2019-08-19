#pragma once
class CGameObject
{
public:
	bool bActive = true;
	bool bStart = false;

	CSpriteRenderer * renderer;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 pivot;
	float fRot;
	D3DXMATRIX mWorld;

	int layer;
	float radius;
	bool* checkLayers;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void Start() {};
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

	void CreateCollider(int layer, float radius);
	void SetCollision(int layer);

	virtual void OnCollision(CGameObject* CollisionObject) {};
};

