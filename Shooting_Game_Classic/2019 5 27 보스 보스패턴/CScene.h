#pragma once

class EnemyEntryInfo
{
public:
	D3DXVECTOR2 enterPos;
	float timer;
	float speed;

	EnemyEntryInfo(D3DXVECTOR2 enterPos, float timer, float speed = 300)
		: enterPos(enterPos), speed(speed), timer(timer)
	{
	}
};

class CScene
{
public:
	list<CBullet*> playerBulletList;

public:
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

public:
	CBoss* boss;

public:
	CPlayer* player;

public:
	CScene();	// Init()
	~CScene();	// Term()
	virtual void Update(float deltaTime);	// Update
	virtual void Render(LPD3DXSPRITE sprite);	// Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	 // MsgProc

public:
	void RectUpdate(float deltaTime);
};
