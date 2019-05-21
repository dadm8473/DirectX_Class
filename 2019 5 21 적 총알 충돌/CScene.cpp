#include "DXUT.h"
#include "Header.h"

CScene::CScene()
	: playerBulletList(), enemyEntryInfo(), enemyList(), enemyEntryTimer(0), currentEnemyIndex(0)
{
	player = new CPlayer(D3DXVECTOR2(512, 384));
	player->parentScene = this;

	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(100, 50), 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(200, -50), 2));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(300, -50), 3));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(400, -50), 4));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(500, -50), 5));
}

CScene::~CScene()
{
	if (player)
		delete player;

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

}

void CScene::Update(float deltaTime)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		player->position.x -= 400 * deltaTime;

	if (GetKeyState(VK_RIGHT) & 0x8000)
		player->position.x += 400 * deltaTime;

	if (GetKeyState(VK_UP) & 0x8000)
		player->position.y -= 400 * deltaTime;

	if (GetKeyState(VK_DOWN) & 0x8000)
		player->position.y += 400 * deltaTime;

	if (GetKeyState('X') & 0x8000)
		player->Attack();

	player->Update(deltaTime);

	enemyEntryTimer += deltaTime;
	while (enemyEntryTimer > enemyEntryInfo[currentEnemyIndex].timer)
	{
		CEnemy* enemy = new CEnemy(enemyEntryInfo[currentEnemyIndex].enterPos, 300);
		enemyList.push_back(enemy);

		currentEnemyIndex++;

		if (currentEnemyIndex >= enemyEntryInfo.size())
		{
			currentEnemyIndex = 0;
			enemyEntryTimer = 0;
			break;
		}
	}

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed == true)
		{
			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed == true)
		{
			delete(*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}

	// 충돌 업데이트
	RectUpdate(deltaTime);
}

void CScene::Render(LPD3DXSPRITE sprite)
{
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	player->Render(sprite);

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);
}

void CScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}

void CScene::RectUpdate(float deltaTime)
{
	// player < enemy

	if (player)
	{
		for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				// 플레이어 죽음
				(*it)->isDestroyed = true;
			}
		}
	}

	// enemy < playerBullet
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;
				(*it2)->hp--;
			}
		}
	}
}