#include "DXUT.h"
#include "Header.h"

CScene::CScene()
	: playerBulletList(), enemyEntryInfo(), enemyList(), enemyEntryTimer(0), currentEnemyIndex(0),
	enemyBulletList(), rebirthTime(2), rebirthTimer(0)
{
	player = new CPlayer(D3DXVECTOR2(512, 384));
	player->parentScene = this;

	map = new CMap();

	boss = new CBoss(D3DXVECTOR2(512, -100));
	boss->parentScene = this;

	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(100, 50), 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(200, -50), 2));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(300, -50), 3));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(400, -50), 4));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(500, -50), 5));
}

CScene::~CScene()
{
	// �÷��̾� �Ҹ���
	if (player)
		delete player;

	// �� ����Ʈ �Ҹ���
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	// ���� �Ҹ���
	if (boss)
		delete boss;

	// �÷��̾� �Ѿ� ����Ʈ �Ҹ���
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

	// �� �Ѿ� ����Ʈ �Ҹ���
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete (*it);
	enemyBulletList.clear();

	// �� �Ҹ���
	if (map)
		delete map;

}

void CScene::Update(float deltaTime)
{
	// �� ������Ʈ
	if (map)
		map->Update(deltaTime);

	// �÷��̾� ������Ʈ
	if (player)
	{
		// �÷��̾� �̵�
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

		// �÷��̾� ������Ʈ
		player->Update(deltaTime);
		
		// �÷��̾� ����
		if (player->invincible)
			player->isDie = false;

		// �÷��̾ �׾��� ���
		if (player->isDie)
		{
			player = NULL;
			delete player;
		}
	}
	else
	{
		// �÷��̾ ���� �� ��Ȱ
		rebirthTimer += deltaTime;
		if (rebirthTimer > rebirthTime)
		{
			rebirthTimer = 0;

			player = new CPlayer(D3DXVECTOR2(512, 384));
			player->parentScene = this;
		}
	}

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

	if (boss)
		boss->Update(deltaTime);

	// �÷��̾� �Ѿ� ������Ʈ
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

	// �� �Ѿ� ������Ʈ
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed == true)
		{
			delete(*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	// �浹 ������Ʈ
	RectUpdate(deltaTime);
}

void CScene::Render(LPD3DXSPRITE sprite)
{
	// �� ����
	if (map)
		map->Render(sprite);
	
	// �÷��̾� �Ѿ� ����
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	// �� �Ѿ� ����
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	// �÷��̾� ����
	if(player)
		player->Render(sprite);

	// �� ����Ʈ ����
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);

	// ���� ����
	if(boss)
		boss->Render(sprite);
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
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}

		for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
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