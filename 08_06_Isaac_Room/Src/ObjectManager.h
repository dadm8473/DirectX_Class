#pragma once


class ObjectManager
{
public:
	std::list<CGameObject*> m_ObjectList;

	ObjectManager();
	~ObjectManager();

	virtual int Start();

	virtual int Update(float dTime);

	virtual int Render();

	virtual int Destroy();
};

bool ObjectSort(const CGameObject* lhs, const CGameObject* rhs);