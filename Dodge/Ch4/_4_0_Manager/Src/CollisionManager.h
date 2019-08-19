#pragma once
#include <list>
using namespace std;

class CollisionManager
{
public:
	list<Collider *> * ColliderLists;
	CollisionManager();
	~CollisionManager();

	bool Collision(Collider * p_Collider);
};

