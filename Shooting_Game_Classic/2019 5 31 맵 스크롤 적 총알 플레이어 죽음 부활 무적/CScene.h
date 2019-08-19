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
public:		// 총알 관련
	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

public:		// 적 관련
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

public:		// 보스 관련
	CBoss* boss;

public:		// 플레이어 관련
	CPlayer* player;
	float rebirthTimer;
	float rebirthTime;

public:		// 맵 관련
	CMap* map;

public:		// 씬 관련
	CScene();	// Init()
	~CScene();	// Term()
	virtual void Update(float deltaTime);	// Update
	virtual void Render(LPD3DXSPRITE sprite);	// Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	 // MsgProc

public:		// 정리
	void RectUpdate(float deltaTime);
};
