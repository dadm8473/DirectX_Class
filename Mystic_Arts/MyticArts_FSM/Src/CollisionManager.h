#pragma once
#include <list>
using namespace std;

class CollisionManager
{
public:
	list<CGameObject*> * colliderLists;
	CollisionManager();
	~CollisionManager();

	bool Collision(CGameObject* p_Collider);

	list<CGameObject*> rigidbodyList;

	bool RigidbodyCollision(CGameObject * gameObject);


	CSpriteRenderer * renderer = NULL;

	bool DrawCollider();
};

