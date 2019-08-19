#pragma once
#include "CGameObject.h"
class Room :
	public CGameObject
{
public:
	Room();
	~Room();

	bool bOpen;
	Door * door[4];
	RECT rect;
	
	std::list<CGameObject*> enemyList;
	std::list<CGameObject*> itemList;

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void OnCollision(CGameObject* CollisionObject);

	void SetEnemy(CGameObject * enemy, D3DXVECTOR2 enemeyPos);
	void SetItem(CGameObject * item, D3DXVECTOR2 itemPos);

	void CheckPlayer();
};

