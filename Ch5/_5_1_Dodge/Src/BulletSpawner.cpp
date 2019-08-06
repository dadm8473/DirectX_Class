#include "DXUT.h"
#include "BulletSpawner.h"

void BulletSpawner::Start()
{
	SpawnTimer = 0;
	Time = 4;
}

void BulletSpawner::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	SpawnTimer += deltaTime;

	if (g_Game.BulletCount > 75)
		return;

	if (SpawnTimer > Time)
	{
		SpawnTimer = 0;

		EnemyBullet* temp = new EnemyBullet;
		int x = rand() % 1024;
		int y = rand() % 2;
		temp->position = D3DXVECTOR2(x, y * 768);

		temp = new EnemyBullet;
		x = rand() % 2;
		y = rand() % 768;
		temp->position = D3DXVECTOR2(x * 1024, y);

		g_Game.BulletCount += 2;

		if (g_Game.TimeScore > 7)
		{
			ChaseBullet* temp = new ChaseBullet;
			int x = rand() % 1024;
			int y = rand() % 2;
			temp->position = D3DXVECTOR2(x, y * 768);

			g_Game.BulletCount += 1;
		}
	}
}
