#pragma once

class Scene : public ObjectManager
{
public:
	bool bNextScene;

	CollisionManager m_CollisionManager;

	Scene();
	~Scene();

	virtual int Start();

	virtual int Update(float deltaTime);

	virtual int Render();

	virtual int Destroy();

	//virtual int Command(CGameObject* p_Source, bool pushUp, DWORD lParam);
};

