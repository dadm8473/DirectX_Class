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

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Update(deltaTime);

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Update(deltaTime);
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
