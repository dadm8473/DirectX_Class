#pragma once
using namespace std;
#include "Component.h"

enum COLLIDER_TYPE
{
	CT_CIRCLE = 0,
	CT_BOX,
};

enum COLLIDER_LAYER
{
	CL_NONE,
	CL_PLAYER,
	CL_BULLET,
	CL_MAX,
};

class Collider :
	public Component
{
public:
	int Type;
	int Layer;
	bool * CheckLayers;

	D3DXVECTOR2 scale;

	Collider(CGameObject * p_trnasform, int p_Layer = 0);
	virtual ~Collider();

	virtual void Start() {}
	virtual void Update(float deltaTime);
	virtual void Destroy() {}

	virtual void OnCollision(CGameObject * CollisionObject) {}
};

