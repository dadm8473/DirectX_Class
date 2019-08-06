#pragma once
class CGameObject
{
public:
	bool bActive = true;
	bool bCollision = false;
	bool bStart = false;

	int type = GAMEOBJECT;

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
	CGameObject(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, bool p_bAnimation, int p_TotalIndex = 0, int p_TotalFrame = 0, float p_Delay = 0);
	virtual ~CGameObject();

	virtual void Start() {};
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

	void CreateCollider(int layer, float radius);
	void SetCollision(int layer);

	virtual void OnCollision(CGameObject* CollisionObject) {};
};