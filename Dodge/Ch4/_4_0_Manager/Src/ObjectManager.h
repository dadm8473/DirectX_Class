#pragma once


class ObjectManager
{
public:
	std::list<CGameObject*> m_ObjectList;

	ObjectManager();
	~ObjectManager();

	int Start();

	int Update(float dTime);

	int Render();

	int Destroy();
};

